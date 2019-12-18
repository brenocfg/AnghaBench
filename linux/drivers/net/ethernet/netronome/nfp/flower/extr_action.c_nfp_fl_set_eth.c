#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_4__ {int len_lw; int /*<<< orphan*/  jump_id; } ;
struct nfp_fl_set_eth {TYPE_2__ head; int /*<<< orphan*/  reserved; int /*<<< orphan*/ * eth_addr_mask; int /*<<< orphan*/ * eth_addr_val; } ;
struct netlink_ext_ack {int dummy; } ;
struct TYPE_3__ {int mask; int val; } ;
struct flow_action_entry {TYPE_1__ mangle; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int ETH_ALEN ; 
 int /*<<< orphan*/  NFP_FL_ACTION_OPCODE_SET_ETHERNET ; 
 int NFP_FL_LW_SIZ ; 
 int /*<<< orphan*/  NL_SET_ERR_MSG_MOD (struct netlink_ext_ack*,char*) ; 
 int /*<<< orphan*/  cpu_to_be16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfp_fl_set_helper32 (int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
nfp_fl_set_eth(const struct flow_action_entry *act, u32 off,
	       struct nfp_fl_set_eth *set_eth, struct netlink_ext_ack *extack)
{
	u32 exact, mask;

	if (off + 4 > ETH_ALEN * 2) {
		NL_SET_ERR_MSG_MOD(extack, "unsupported offload: invalid pedit ethernet action");
		return -EOPNOTSUPP;
	}

	mask = ~act->mangle.mask;
	exact = act->mangle.val;

	if (exact & ~mask) {
		NL_SET_ERR_MSG_MOD(extack, "unsupported offload: invalid pedit ethernet action");
		return -EOPNOTSUPP;
	}

	nfp_fl_set_helper32(exact, mask, &set_eth->eth_addr_val[off],
			    &set_eth->eth_addr_mask[off]);

	set_eth->reserved = cpu_to_be16(0);
	set_eth->head.jump_id = NFP_FL_ACTION_OPCODE_SET_ETHERNET;
	set_eth->head.len_lw = sizeof(*set_eth) >> NFP_FL_LW_SIZ;

	return 0;
}