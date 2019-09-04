#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct fw_vi_mac_raw {void* raw_idx_pkd; int /*<<< orphan*/ * data1m; int /*<<< orphan*/ * data1; int /*<<< orphan*/  data0m_pkd; void* data0_pkd; } ;
struct TYPE_2__ {struct fw_vi_mac_raw raw; } ;
struct fw_vi_mac_cmd {void* freemacs_to_len16; void* op_to_viid; TYPE_1__ u; } ;
struct adapter {int /*<<< orphan*/  mbox; } ;
typedef  int /*<<< orphan*/  c ;

/* Variables and functions */
 int /*<<< orphan*/  DATALKPTYPE_M ; 
 int DATALKPTYPE_V (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DATAPORTNUM_M ; 
 int DATAPORTNUM_V (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int FW_CMD_LEN16_V (int) ; 
 int FW_CMD_OP_V (int /*<<< orphan*/ ) ; 
 int FW_CMD_REQUEST_F ; 
 int FW_CMD_WRITE_F ; 
 int /*<<< orphan*/  FW_VI_MAC_CMD ; 
 int FW_VI_MAC_CMD_ENTRY_TYPE_V (int /*<<< orphan*/ ) ; 
 int FW_VI_MAC_CMD_RAW_IDX_G (int /*<<< orphan*/ ) ; 
 int FW_VI_MAC_CMD_RAW_IDX_V (unsigned int) ; 
 int FW_VI_MAC_CMD_VIID_V (unsigned int) ; 
 int /*<<< orphan*/  FW_VI_MAC_TYPE_RAW ; 
 int /*<<< orphan*/  be32_to_cpu (void*) ; 
 void* cpu_to_be32 (int) ; 
 int /*<<< orphan*/  cpu_to_be64 (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct fw_vi_mac_cmd*,int /*<<< orphan*/ ,int) ; 
 int t4_wr_mbox_meat (struct adapter*,int /*<<< orphan*/ ,struct fw_vi_mac_cmd*,int,struct fw_vi_mac_cmd*,int) ; 

int t4_alloc_raw_mac_filt(struct adapter *adap, unsigned int viid,
			  const u8 *addr, const u8 *mask, unsigned int idx,
			  u8 lookup_type, u8 port_id, bool sleep_ok)
{
	int ret = 0;
	struct fw_vi_mac_cmd c;
	struct fw_vi_mac_raw *p = &c.u.raw;
	u32 val;

	memset(&c, 0, sizeof(c));
	c.op_to_viid = cpu_to_be32(FW_CMD_OP_V(FW_VI_MAC_CMD) |
				   FW_CMD_REQUEST_F | FW_CMD_WRITE_F |
				   FW_VI_MAC_CMD_VIID_V(viid));
	val = FW_CMD_LEN16_V(1) |
	      FW_VI_MAC_CMD_ENTRY_TYPE_V(FW_VI_MAC_TYPE_RAW);
	c.freemacs_to_len16 = cpu_to_be32(val);

	/* Specify that this is an inner mac address */
	p->raw_idx_pkd = cpu_to_be32(FW_VI_MAC_CMD_RAW_IDX_V(idx));

	/* Lookup Type. Outer header: 0, Inner header: 1 */
	p->data0_pkd = cpu_to_be32(DATALKPTYPE_V(lookup_type) |
				   DATAPORTNUM_V(port_id));
	/* Lookup mask and port mask */
	p->data0m_pkd = cpu_to_be64(DATALKPTYPE_V(DATALKPTYPE_M) |
				    DATAPORTNUM_V(DATAPORTNUM_M));

	/* Copy the address and the mask */
	memcpy((u8 *)&p->data1[0] + 2, addr, ETH_ALEN);
	memcpy((u8 *)&p->data1m[0] + 2, mask, ETH_ALEN);

	ret = t4_wr_mbox_meat(adap, adap->mbox, &c, sizeof(c), &c, sleep_ok);
	if (ret == 0) {
		ret = FW_VI_MAC_CMD_RAW_IDX_G(be32_to_cpu(p->raw_idx_pkd));
		if (ret != idx)
			ret = -ENOMEM;
	}

	return ret;
}