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
struct qedf_ctx {int prio; int vlan_id; int /*<<< orphan*/  dbg_ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  QEDF_INFO (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  QEDF_LOG_DISC ; 
 int VLAN_PRIO_SHIFT ; 

void qedf_set_vlan_id(struct qedf_ctx *qedf, int vlan_id)
{
	int vlan_id_tmp = 0;

	vlan_id_tmp = vlan_id  | (qedf->prio << VLAN_PRIO_SHIFT);
	qedf->vlan_id = vlan_id_tmp;
	QEDF_INFO(&qedf->dbg_ctx, QEDF_LOG_DISC,
		  "Setting vlan_id=0x%04x prio=%d.\n",
		  vlan_id_tmp, qedf->prio);
}