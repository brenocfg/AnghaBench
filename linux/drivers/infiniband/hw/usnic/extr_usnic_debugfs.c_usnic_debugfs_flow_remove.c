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
struct usnic_ib_qp_grp_flow {int /*<<< orphan*/  dbgfs_dentry; } ;

/* Variables and functions */
 int /*<<< orphan*/  debugfs_remove (int /*<<< orphan*/ ) ; 

void usnic_debugfs_flow_remove(struct usnic_ib_qp_grp_flow *qp_flow)
{
	debugfs_remove(qp_flow->dbgfs_dentry);
}