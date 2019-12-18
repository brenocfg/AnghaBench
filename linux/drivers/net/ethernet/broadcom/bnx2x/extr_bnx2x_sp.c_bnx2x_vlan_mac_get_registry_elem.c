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
struct bnx2x_vlan_mac_registry_elem {int /*<<< orphan*/  vlan_mac_flags; int /*<<< orphan*/  u; int /*<<< orphan*/  cam_offset; } ;
struct bnx2x_vlan_mac_obj {struct bnx2x_vlan_mac_registry_elem* (* check_del ) (struct bnx2x*,struct bnx2x_vlan_mac_obj*,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* get_cam_offset ) (struct bnx2x_vlan_mac_obj*,int /*<<< orphan*/ *) ;} ;
struct TYPE_3__ {int cmd; int /*<<< orphan*/  u; int /*<<< orphan*/  vlan_mac_flags; } ;
struct TYPE_4__ {TYPE_1__ vlan_mac; } ;
struct bnx2x_exeq_elem {TYPE_2__ cmd_data; } ;
struct bnx2x {int dummy; } ;
typedef  enum bnx2x_vlan_mac_cmd { ____Placeholder_bnx2x_vlan_mac_cmd } bnx2x_vlan_mac_cmd ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_MSG_SP ; 
 int BNX2X_VLAN_MAC_ADD ; 
 int BNX2X_VLAN_MAC_MOVE ; 
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  kfree (struct bnx2x_vlan_mac_registry_elem*) ; 
 struct bnx2x_vlan_mac_registry_elem* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stub1 (struct bnx2x_vlan_mac_obj*,int /*<<< orphan*/ *) ; 
 struct bnx2x_vlan_mac_registry_elem* stub2 (struct bnx2x*,struct bnx2x_vlan_mac_obj*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int bnx2x_vlan_mac_get_registry_elem(
	struct bnx2x *bp,
	struct bnx2x_vlan_mac_obj *o,
	struct bnx2x_exeq_elem *elem,
	bool restore,
	struct bnx2x_vlan_mac_registry_elem **re)
{
	enum bnx2x_vlan_mac_cmd cmd = elem->cmd_data.vlan_mac.cmd;
	struct bnx2x_vlan_mac_registry_elem *reg_elem;

	/* Allocate a new registry element if needed. */
	if (!restore &&
	    ((cmd == BNX2X_VLAN_MAC_ADD) || (cmd == BNX2X_VLAN_MAC_MOVE))) {
		reg_elem = kzalloc(sizeof(*reg_elem), GFP_ATOMIC);
		if (!reg_elem)
			return -ENOMEM;

		/* Get a new CAM offset */
		if (!o->get_cam_offset(o, &reg_elem->cam_offset)) {
			/* This shall never happen, because we have checked the
			 * CAM availability in the 'validate'.
			 */
			WARN_ON(1);
			kfree(reg_elem);
			return -EINVAL;
		}

		DP(BNX2X_MSG_SP, "Got cam offset %d\n", reg_elem->cam_offset);

		/* Set a VLAN-MAC data */
		memcpy(&reg_elem->u, &elem->cmd_data.vlan_mac.u,
			  sizeof(reg_elem->u));

		/* Copy the flags (needed for DEL and RESTORE flows) */
		reg_elem->vlan_mac_flags =
			elem->cmd_data.vlan_mac.vlan_mac_flags;
	} else /* DEL, RESTORE */
		reg_elem = o->check_del(bp, o, &elem->cmd_data.vlan_mac.u);

	*re = reg_elem;
	return 0;
}