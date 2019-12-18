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
struct qib_ibdev {struct dentry* qib_ibdev_dbg; } ;
struct dentry {int dummy; } ;
typedef  int /*<<< orphan*/  name ;
struct TYPE_2__ {int unit; } ;

/* Variables and functions */
 int /*<<< orphan*/  _ctx_stats_file_ops ; 
 int /*<<< orphan*/  _opcode_stats_file_ops ; 
 int /*<<< orphan*/  _qp_stats_file_ops ; 
 TYPE_1__* dd_from_dev (struct qib_ibdev*) ; 
 struct dentry* debugfs_create_dir (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugfs_create_file (char*,int,struct dentry*,struct qib_ibdev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qib_dbg_root ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 

void qib_dbg_ibdev_init(struct qib_ibdev *ibd)
{
	struct dentry *root;
	char name[10];

	snprintf(name, sizeof(name), "qib%d", dd_from_dev(ibd)->unit);
	root = debugfs_create_dir(name, qib_dbg_root);
	ibd->qib_ibdev_dbg = root;

	debugfs_create_file("opcode_stats", 0400, root, ibd,
			    &_opcode_stats_file_ops);
	debugfs_create_file("ctx_stats", 0400, root, ibd, &_ctx_stats_file_ops);
	debugfs_create_file("qp_stats", 0400, root, ibd, &_qp_stats_file_ops);
}