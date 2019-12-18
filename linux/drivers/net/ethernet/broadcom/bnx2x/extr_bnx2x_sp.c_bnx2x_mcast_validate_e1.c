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
struct bnx2x_mcast_ramrod_params {int mcast_list_len; struct bnx2x_mcast_obj* mcast_obj; } ;
struct bnx2x_mcast_obj {int (* get_registry_size ) (struct bnx2x_mcast_obj*) ;scalar_t__ max_cmd_len; int /*<<< orphan*/  total_pending_num; int /*<<< orphan*/  (* set_registry_size ) (struct bnx2x_mcast_obj*,scalar_t__) ;} ;
struct bnx2x {int dummy; } ;
typedef  enum bnx2x_mcast_cmd { ____Placeholder_bnx2x_mcast_cmd } bnx2x_mcast_cmd ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_ERR (char*,...) ; 
#define  BNX2X_MCAST_CMD_ADD 131 
#define  BNX2X_MCAST_CMD_CONT 130 
#define  BNX2X_MCAST_CMD_DEL 129 
#define  BNX2X_MCAST_CMD_RESTORE 128 
 int BNX2X_MCAST_CMD_SET ; 
 int /*<<< orphan*/  BNX2X_MSG_SP ; 
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*,scalar_t__,...) ; 
 int EINVAL ; 
 int stub1 (struct bnx2x_mcast_obj*) ; 
 int /*<<< orphan*/  stub2 (struct bnx2x_mcast_obj*,scalar_t__) ; 
 int /*<<< orphan*/  stub3 (struct bnx2x_mcast_obj*,scalar_t__) ; 

__attribute__((used)) static int bnx2x_mcast_validate_e1(struct bnx2x *bp,
				   struct bnx2x_mcast_ramrod_params *p,
				   enum bnx2x_mcast_cmd cmd)
{
	struct bnx2x_mcast_obj *o = p->mcast_obj;
	int reg_sz = o->get_registry_size(o);

	if (cmd == BNX2X_MCAST_CMD_SET) {
		BNX2X_ERR("Can't use `set' command on e1!\n");
		return -EINVAL;
	}

	switch (cmd) {
	/* DEL command deletes all currently configured MACs */
	case BNX2X_MCAST_CMD_DEL:
		o->set_registry_size(o, 0);
		/* fall through */

	/* RESTORE command will restore the entire multicast configuration */
	case BNX2X_MCAST_CMD_RESTORE:
		p->mcast_list_len = reg_sz;
		DP(BNX2X_MSG_SP, "Command %d, p->mcast_list_len=%d\n",
		   cmd, p->mcast_list_len);
		break;

	case BNX2X_MCAST_CMD_ADD:
	case BNX2X_MCAST_CMD_CONT:
		/* Multicast MACs on 57710 are configured as unicast MACs and
		 * there is only a limited number of CAM entries for that
		 * matter.
		 */
		if (p->mcast_list_len > o->max_cmd_len) {
			BNX2X_ERR("Can't configure more than %d multicast MACs on 57710\n",
				  o->max_cmd_len);
			return -EINVAL;
		}
		/* Every configured MAC should be cleared if DEL command is
		 * called. Only the last ADD command is relevant as long as
		 * every ADD commands overrides the previous configuration.
		 */
		DP(BNX2X_MSG_SP, "p->mcast_list_len=%d\n", p->mcast_list_len);
		if (p->mcast_list_len > 0)
			o->set_registry_size(o, p->mcast_list_len);

		break;

	default:
		BNX2X_ERR("Unknown command: %d\n", cmd);
		return -EINVAL;
	}

	/* We want to ensure that commands are executed one by one for 57710.
	 * Therefore each none-empty command will consume o->max_cmd_len.
	 */
	if (p->mcast_list_len)
		o->total_pending_num += o->max_cmd_len;

	return 0;
}