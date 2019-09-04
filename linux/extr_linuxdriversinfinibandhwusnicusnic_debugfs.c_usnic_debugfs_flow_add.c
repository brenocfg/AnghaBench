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
struct usnic_ib_qp_grp_flow {int /*<<< orphan*/  dbgfs_dentry; TYPE_1__* flow; int /*<<< orphan*/  dentry_name; } ;
struct TYPE_2__ {int /*<<< orphan*/  flow_id; } ;

/* Variables and functions */
 scalar_t__ IS_ERR_OR_NULL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_IRUGO ; 
 int /*<<< orphan*/  debugfs_create_file (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct usnic_ib_qp_grp_flow*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flowinfo_ops ; 
 int /*<<< orphan*/  flows_dentry ; 
 int /*<<< orphan*/  scnprintf (int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usnic_err (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void usnic_debugfs_flow_add(struct usnic_ib_qp_grp_flow *qp_flow)
{
	if (IS_ERR_OR_NULL(flows_dentry))
		return;

	scnprintf(qp_flow->dentry_name, sizeof(qp_flow->dentry_name),
			"%u", qp_flow->flow->flow_id);
	qp_flow->dbgfs_dentry = debugfs_create_file(qp_flow->dentry_name,
							S_IRUGO,
							flows_dentry,
							qp_flow,
							&flowinfo_ops);
	if (IS_ERR_OR_NULL(qp_flow->dbgfs_dentry)) {
		usnic_err("Failed to create dbg fs entry for flow %u with error %ld\n",
				qp_flow->flow->flow_id,
				PTR_ERR(qp_flow->dbgfs_dentry));
	}
}