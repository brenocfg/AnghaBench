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
struct fw_vi_mac_exact {int /*<<< orphan*/  macaddr; int /*<<< orphan*/  valid_to_idx; } ;
struct TYPE_2__ {struct fw_vi_mac_exact* exact; } ;
struct fw_vi_mac_cmd {TYPE_1__ u; void* freemacs_to_len16; void* op_to_viid; } ;
struct adapter {int /*<<< orphan*/  mbox; } ;
typedef  int /*<<< orphan*/  c ;

/* Variables and functions */
 int FW_CMD_EXEC_V (int /*<<< orphan*/ ) ; 
 int FW_CMD_LEN16_V (int) ; 
 int FW_CMD_OP_V (int /*<<< orphan*/ ) ; 
 int FW_CMD_REQUEST_F ; 
 int FW_CMD_WRITE_F ; 
 int /*<<< orphan*/  FW_VI_MAC_CMD ; 
 int FW_VI_MAC_CMD_ENTRY_TYPE_V (int /*<<< orphan*/ ) ; 
 int FW_VI_MAC_CMD_FREEMACS_V (int /*<<< orphan*/ ) ; 
 int FW_VI_MAC_CMD_IDX_V (int) ; 
 int FW_VI_MAC_CMD_VALID_F ; 
 int FW_VI_MAC_CMD_VIID_V (unsigned int) ; 
 int /*<<< orphan*/  FW_VI_MAC_TYPE_EXACTMAC ; 
 int /*<<< orphan*/  cpu_to_be16 (int) ; 
 void* cpu_to_be32 (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (struct fw_vi_mac_cmd*,int /*<<< orphan*/ ,int) ; 
 int t4_wr_mbox_meat (struct adapter*,int /*<<< orphan*/ ,struct fw_vi_mac_cmd*,int,struct fw_vi_mac_cmd*,int) ; 

int t4_free_encap_mac_filt(struct adapter *adap, unsigned int viid,
			   int idx, bool sleep_ok)
{
	struct fw_vi_mac_exact *p;
	u8 addr[] = {0, 0, 0, 0, 0, 0};
	struct fw_vi_mac_cmd c;
	int ret = 0;
	u32 exact;

	memset(&c, 0, sizeof(c));
	c.op_to_viid = cpu_to_be32(FW_CMD_OP_V(FW_VI_MAC_CMD) |
				   FW_CMD_REQUEST_F | FW_CMD_WRITE_F |
				   FW_CMD_EXEC_V(0) |
				   FW_VI_MAC_CMD_VIID_V(viid));
	exact = FW_VI_MAC_CMD_ENTRY_TYPE_V(FW_VI_MAC_TYPE_EXACTMAC);
	c.freemacs_to_len16 = cpu_to_be32(FW_VI_MAC_CMD_FREEMACS_V(0) |
					  exact |
					  FW_CMD_LEN16_V(1));
	p = c.u.exact;
	p->valid_to_idx = cpu_to_be16(FW_VI_MAC_CMD_VALID_F |
				      FW_VI_MAC_CMD_IDX_V(idx));
	memcpy(p->macaddr, addr, sizeof(p->macaddr));
	ret = t4_wr_mbox_meat(adap, adap->mbox, &c, sizeof(c), &c, sleep_ok);
	return ret;
}