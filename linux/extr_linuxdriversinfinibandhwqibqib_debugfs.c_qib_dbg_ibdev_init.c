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
struct qib_ibdev {int /*<<< orphan*/  qib_ibdev_dbg; } ;
typedef  int /*<<< orphan*/  name ;
struct TYPE_2__ {int unit; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFS_FILE_CREATE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctx_stats ; 
 TYPE_1__* dd_from_dev (struct qib_ibdev*) ; 
 int /*<<< orphan*/  debugfs_create_dir (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  opcode_stats ; 
 int /*<<< orphan*/  pr_warn (char*,char*) ; 
 int /*<<< orphan*/  qib_dbg_root ; 
 int /*<<< orphan*/  qp_stats ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 

void qib_dbg_ibdev_init(struct qib_ibdev *ibd)
{
	char name[10];

	snprintf(name, sizeof(name), "qib%d", dd_from_dev(ibd)->unit);
	ibd->qib_ibdev_dbg = debugfs_create_dir(name, qib_dbg_root);
	if (!ibd->qib_ibdev_dbg) {
		pr_warn("create of %s failed\n", name);
		return;
	}
	DEBUGFS_FILE_CREATE(opcode_stats);
	DEBUGFS_FILE_CREATE(ctx_stats);
	DEBUGFS_FILE_CREATE(qp_stats);
}