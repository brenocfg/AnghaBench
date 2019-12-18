#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u64 ;
typedef  int u32 ;
struct sk_buff {int dummy; } ;
struct fw_ri_tpte {void* len_hi; void* dca_mwbcnt_pstag; void* va_lo_fbo; void* va_hi; void* len_lo; void* nosnoop_pbladdr; void* locread_to_qpid; void* valid_to_pdid; } ;
struct c4iw_wr_wait {int dummy; } ;
struct TYPE_11__ {scalar_t__ cur; scalar_t__ max; int /*<<< orphan*/  fail; } ;
struct TYPE_12__ {int /*<<< orphan*/  lock; TYPE_5__ stag; } ;
struct TYPE_10__ {int /*<<< orphan*/  tpt_table; } ;
struct TYPE_9__ {TYPE_2__* vr; } ;
struct c4iw_rdev {TYPE_6__ stats; TYPE_4__ resource; TYPE_3__ lldi; } ;
typedef  enum fw_ri_stag_type { ____Placeholder_fw_ri_stag_type } fw_ri_stag_type ;
typedef  enum fw_ri_mem_perms { ____Placeholder_fw_ri_mem_perms } fw_ri_mem_perms ;
typedef  int /*<<< orphan*/  atomic_t ;
struct TYPE_7__ {int start; } ;
struct TYPE_8__ {TYPE_1__ stag; } ;

/* Variables and functions */
 int EIO ; 
 int ENOMEM ; 
 int FW_RI_TPTE_ADDRTYPE_V (int /*<<< orphan*/ ) ; 
 int FW_RI_TPTE_MWBINDEN_F ; 
 int FW_RI_TPTE_PBLADDR_V (int) ; 
 int FW_RI_TPTE_PDID_V (int) ; 
 int FW_RI_TPTE_PERM_V (int) ; 
 int FW_RI_TPTE_PS_V (int) ; 
 int FW_RI_TPTE_STAGKEY_M ; 
 int FW_RI_TPTE_STAGKEY_V (int) ; 
 int FW_RI_TPTE_STAGSTATE_V (int) ; 
 int FW_RI_TPTE_STAGTYPE_V (int) ; 
 int FW_RI_TPTE_VALID_F ; 
 int /*<<< orphan*/  FW_RI_VA_BASED_TO ; 
 int /*<<< orphan*/  FW_RI_ZERO_BASED_TO ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int PBL_OFF (struct c4iw_rdev*,int) ; 
 int T4_STAG_UNSET ; 
 int atomic_inc_return (int /*<<< orphan*/ *) ; 
 scalar_t__ c4iw_fatal_error (struct c4iw_rdev*) ; 
 int c4iw_get_resource (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  c4iw_put_resource (int /*<<< orphan*/ *,int) ; 
 void* cpu_to_be32 (int) ; 
 int /*<<< orphan*/  kfree (struct fw_ri_tpte*) ; 
 struct fw_ri_tpte* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct fw_ri_tpte*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,int,int,int,int) ; 
 int write_adapter_mem (struct c4iw_rdev*,int,int,struct fw_ri_tpte*,struct sk_buff*,struct c4iw_wr_wait*) ; 

__attribute__((used)) static int write_tpt_entry(struct c4iw_rdev *rdev, u32 reset_tpt_entry,
			   u32 *stag, u8 stag_state, u32 pdid,
			   enum fw_ri_stag_type type, enum fw_ri_mem_perms perm,
			   int bind_enabled, u32 zbva, u64 to,
			   u64 len, u8 page_size, u32 pbl_size, u32 pbl_addr,
			   struct sk_buff *skb, struct c4iw_wr_wait *wr_waitp)
{
	int err;
	struct fw_ri_tpte *tpt;
	u32 stag_idx;
	static atomic_t key;

	if (c4iw_fatal_error(rdev))
		return -EIO;

	tpt = kmalloc(sizeof(*tpt), GFP_KERNEL);
	if (!tpt)
		return -ENOMEM;

	stag_state = stag_state > 0;
	stag_idx = (*stag) >> 8;

	if ((!reset_tpt_entry) && (*stag == T4_STAG_UNSET)) {
		stag_idx = c4iw_get_resource(&rdev->resource.tpt_table);
		if (!stag_idx) {
			mutex_lock(&rdev->stats.lock);
			rdev->stats.stag.fail++;
			mutex_unlock(&rdev->stats.lock);
			kfree(tpt);
			return -ENOMEM;
		}
		mutex_lock(&rdev->stats.lock);
		rdev->stats.stag.cur += 32;
		if (rdev->stats.stag.cur > rdev->stats.stag.max)
			rdev->stats.stag.max = rdev->stats.stag.cur;
		mutex_unlock(&rdev->stats.lock);
		*stag = (stag_idx << 8) | (atomic_inc_return(&key) & 0xff);
	}
	pr_debug("stag_state 0x%0x type 0x%0x pdid 0x%0x, stag_idx 0x%x\n",
		 stag_state, type, pdid, stag_idx);

	/* write TPT entry */
	if (reset_tpt_entry)
		memset(tpt, 0, sizeof(*tpt));
	else {
		tpt->valid_to_pdid = cpu_to_be32(FW_RI_TPTE_VALID_F |
			FW_RI_TPTE_STAGKEY_V((*stag & FW_RI_TPTE_STAGKEY_M)) |
			FW_RI_TPTE_STAGSTATE_V(stag_state) |
			FW_RI_TPTE_STAGTYPE_V(type) | FW_RI_TPTE_PDID_V(pdid));
		tpt->locread_to_qpid = cpu_to_be32(FW_RI_TPTE_PERM_V(perm) |
			(bind_enabled ? FW_RI_TPTE_MWBINDEN_F : 0) |
			FW_RI_TPTE_ADDRTYPE_V((zbva ? FW_RI_ZERO_BASED_TO :
						      FW_RI_VA_BASED_TO))|
			FW_RI_TPTE_PS_V(page_size));
		tpt->nosnoop_pbladdr = !pbl_size ? 0 : cpu_to_be32(
			FW_RI_TPTE_PBLADDR_V(PBL_OFF(rdev, pbl_addr)>>3));
		tpt->len_lo = cpu_to_be32((u32)(len & 0xffffffffUL));
		tpt->va_hi = cpu_to_be32((u32)(to >> 32));
		tpt->va_lo_fbo = cpu_to_be32((u32)(to & 0xffffffffUL));
		tpt->dca_mwbcnt_pstag = cpu_to_be32(0);
		tpt->len_hi = cpu_to_be32((u32)(len >> 32));
	}
	err = write_adapter_mem(rdev, stag_idx +
				(rdev->lldi.vr->stag.start >> 5),
				sizeof(*tpt), tpt, skb, wr_waitp);

	if (reset_tpt_entry) {
		c4iw_put_resource(&rdev->resource.tpt_table, stag_idx);
		mutex_lock(&rdev->stats.lock);
		rdev->stats.stag.cur -= 32;
		mutex_unlock(&rdev->stats.lock);
	}
	kfree(tpt);
	return err;
}