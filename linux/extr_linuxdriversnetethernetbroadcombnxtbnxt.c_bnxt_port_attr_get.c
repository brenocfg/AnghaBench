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
struct TYPE_3__ {int id_len; int /*<<< orphan*/  id; } ;
struct TYPE_4__ {TYPE_1__ ppid; } ;
struct switchdev_attr {int id; TYPE_2__ u; } ;
struct bnxt {scalar_t__ eswitch_mode; int /*<<< orphan*/  switch_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNXT_PF (struct bnxt*) ; 
 scalar_t__ DEVLINK_ESWITCH_MODE_SWITCHDEV ; 
 int EOPNOTSUPP ; 
#define  SWITCHDEV_ATTR_ID_PORT_PARENT_ID 128 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int bnxt_port_attr_get(struct bnxt *bp, struct switchdev_attr *attr)
{
	if (bp->eswitch_mode != DEVLINK_ESWITCH_MODE_SWITCHDEV)
		return -EOPNOTSUPP;

	/* The PF and it's VF-reps only support the switchdev framework */
	if (!BNXT_PF(bp))
		return -EOPNOTSUPP;

	switch (attr->id) {
	case SWITCHDEV_ATTR_ID_PORT_PARENT_ID:
		attr->u.ppid.id_len = sizeof(bp->switch_id);
		memcpy(attr->u.ppid.id, bp->switch_id, attr->u.ppid.id_len);
		break;
	default:
		return -EOPNOTSUPP;
	}
	return 0;
}