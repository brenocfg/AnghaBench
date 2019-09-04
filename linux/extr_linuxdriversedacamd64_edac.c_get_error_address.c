#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u8 ;
typedef  int u64 ;
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct mem_ctl_info {struct amd64_pvt* pvt_info; } ;
struct mce {int addr; int /*<<< orphan*/  extcpu; } ;
struct amd64_pvt {int fam; int /*<<< orphan*/  F1; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRAM_LOCAL_NODE_BASE ; 
 int /*<<< orphan*/  DRAM_LOCAL_NODE_LIM ; 
 int GENMASK_ULL (int,int) ; 
 int __fls (int) ; 
 int /*<<< orphan*/  amd64_read_pci_cfg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  amd_get_nb_id (int /*<<< orphan*/ ) ; 
 struct mem_ctl_info* edac_mc_find (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u64 get_error_address(struct amd64_pvt *pvt, struct mce *m)
{
	u16 mce_nid = amd_get_nb_id(m->extcpu);
	struct mem_ctl_info *mci;
	u8 start_bit = 1;
	u8 end_bit   = 47;
	u64 addr;

	mci = edac_mc_find(mce_nid);
	if (!mci)
		return 0;

	pvt = mci->pvt_info;

	if (pvt->fam == 0xf) {
		start_bit = 3;
		end_bit   = 39;
	}

	addr = m->addr & GENMASK_ULL(end_bit, start_bit);

	/*
	 * Erratum 637 workaround
	 */
	if (pvt->fam == 0x15) {
		u64 cc6_base, tmp_addr;
		u32 tmp;
		u8 intlv_en;

		if ((addr & GENMASK_ULL(47, 24)) >> 24 != 0x00fdf7)
			return addr;


		amd64_read_pci_cfg(pvt->F1, DRAM_LOCAL_NODE_LIM, &tmp);
		intlv_en = tmp >> 21 & 0x7;

		/* add [47:27] + 3 trailing bits */
		cc6_base  = (tmp & GENMASK_ULL(20, 0)) << 3;

		/* reverse and add DramIntlvEn */
		cc6_base |= intlv_en ^ 0x7;

		/* pin at [47:24] */
		cc6_base <<= 24;

		if (!intlv_en)
			return cc6_base | (addr & GENMASK_ULL(23, 0));

		amd64_read_pci_cfg(pvt->F1, DRAM_LOCAL_NODE_BASE, &tmp);

							/* faster log2 */
		tmp_addr  = (addr & GENMASK_ULL(23, 12)) << __fls(intlv_en + 1);

		/* OR DramIntlvSel into bits [14:12] */
		tmp_addr |= (tmp & GENMASK_ULL(23, 21)) >> 9;

		/* add remaining [11:0] bits from original MC4_ADDR */
		tmp_addr |= addr & GENMASK_ULL(11, 0);

		return cc6_base | tmp_addr;
	}

	return addr;
}