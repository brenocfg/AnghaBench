#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct hfi1_ibdev {TYPE_1__* fault; struct dentry* hfi1_ibdev_dbg; } ;
struct dentry {int dummy; } ;
struct TYPE_6__ {int interval; int stacktrace_depth; scalar_t__ verbose; int /*<<< orphan*/ * dname; int /*<<< orphan*/  require_end; } ;
struct TYPE_5__ {int enable; int opcode; int suppress_err; int /*<<< orphan*/  direction; int /*<<< orphan*/  dir; scalar_t__ fault_skip_usec; scalar_t__ fault_skip; TYPE_3__ attr; int /*<<< orphan*/  opcodes; scalar_t__ skip; } ;

/* Variables and functions */
 int BITS_PER_BYTE ; 
 int /*<<< orphan*/  DEBUGFS_SEQ_FILE_CREATE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct hfi1_ibdev*) ; 
 int ENOENT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HFI1_FAULT_DIR_TXRX ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ULONG_MAX ; 
 int /*<<< orphan*/  __fault_opcodes_fops ; 
 int /*<<< orphan*/  bitmap_zero (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  debugfs_create_bool (char*,int,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  debugfs_create_file (char*,int,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugfs_create_u64 (char*,int,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  debugfs_create_u8 (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fault_create_debugfs_attr (char*,struct dentry*,TYPE_3__*) ; 
 int /*<<< orphan*/  fault_stats ; 
 int /*<<< orphan*/  hfi1_fault_exit_debugfs (struct hfi1_ibdev*) ; 
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 
 TYPE_1__* kzalloc (int,int /*<<< orphan*/ ) ; 

int hfi1_fault_init_debugfs(struct hfi1_ibdev *ibd)
{
	struct dentry *parent = ibd->hfi1_ibdev_dbg;

	ibd->fault = kzalloc(sizeof(*ibd->fault), GFP_KERNEL);
	if (!ibd->fault)
		return -ENOMEM;

	ibd->fault->attr.interval = 1;
	ibd->fault->attr.require_end = ULONG_MAX;
	ibd->fault->attr.stacktrace_depth = 32;
	ibd->fault->attr.dname = NULL;
	ibd->fault->attr.verbose = 0;
	ibd->fault->enable = false;
	ibd->fault->opcode = false;
	ibd->fault->fault_skip = 0;
	ibd->fault->skip = 0;
	ibd->fault->direction = HFI1_FAULT_DIR_TXRX;
	ibd->fault->suppress_err = false;
	bitmap_zero(ibd->fault->opcodes,
		    sizeof(ibd->fault->opcodes) * BITS_PER_BYTE);

	ibd->fault->dir =
		fault_create_debugfs_attr("fault", parent,
					  &ibd->fault->attr);
	if (IS_ERR(ibd->fault->dir)) {
		kfree(ibd->fault);
		ibd->fault = NULL;
		return -ENOENT;
	}

	DEBUGFS_SEQ_FILE_CREATE(fault_stats, ibd->fault->dir, ibd);
	if (!debugfs_create_bool("enable", 0600, ibd->fault->dir,
				 &ibd->fault->enable))
		goto fail;
	if (!debugfs_create_bool("suppress_err", 0600,
				 ibd->fault->dir,
				 &ibd->fault->suppress_err))
		goto fail;
	if (!debugfs_create_bool("opcode_mode", 0600, ibd->fault->dir,
				 &ibd->fault->opcode))
		goto fail;
	if (!debugfs_create_file("opcodes", 0600, ibd->fault->dir,
				 ibd->fault, &__fault_opcodes_fops))
		goto fail;
	if (!debugfs_create_u64("skip_pkts", 0600,
				ibd->fault->dir,
				&ibd->fault->fault_skip))
		goto fail;
	if (!debugfs_create_u64("skip_usec", 0600,
				ibd->fault->dir,
				&ibd->fault->fault_skip_usec))
		goto fail;
	if (!debugfs_create_u8("direction", 0600, ibd->fault->dir,
			       &ibd->fault->direction))
		goto fail;

	return 0;
fail:
	hfi1_fault_exit_debugfs(ibd);
	return -ENOMEM;
}