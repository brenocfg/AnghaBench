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
struct TYPE_2__ {int interval; int stacktrace_depth; scalar_t__ verbose; int /*<<< orphan*/ * dname; int /*<<< orphan*/  require_end; } ;
struct hfi1_ibdev {int enable; int opcode; int suppress_err; int /*<<< orphan*/  direction; struct hfi1_ibdev* fault; int /*<<< orphan*/  fault_skip_usec; int /*<<< orphan*/  fault_skip; struct dentry* dir; TYPE_1__ attr; int /*<<< orphan*/  opcodes; scalar_t__ skip; struct dentry* hfi1_ibdev_dbg; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int BITS_PER_BYTE ; 
 int ENOENT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HFI1_FAULT_DIR_TXRX ; 
 scalar_t__ IS_ERR (struct dentry*) ; 
 int /*<<< orphan*/  ULONG_MAX ; 
 int /*<<< orphan*/  __fault_opcodes_fops ; 
 int /*<<< orphan*/  _fault_stats_file_ops ; 
 int /*<<< orphan*/  bitmap_zero (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  debugfs_create_bool (char*,int,struct dentry*,int*) ; 
 int /*<<< orphan*/  debugfs_create_file (char*,int,struct dentry*,struct hfi1_ibdev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugfs_create_u64 (char*,int,struct dentry*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugfs_create_u8 (char*,int,struct dentry*,int /*<<< orphan*/ *) ; 
 struct dentry* fault_create_debugfs_attr (char*,struct dentry*,TYPE_1__*) ; 
 int /*<<< orphan*/  kfree (struct hfi1_ibdev*) ; 
 struct hfi1_ibdev* kzalloc (int,int /*<<< orphan*/ ) ; 

int hfi1_fault_init_debugfs(struct hfi1_ibdev *ibd)
{
	struct dentry *parent = ibd->hfi1_ibdev_dbg;
	struct dentry *fault_dir;

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

	fault_dir =
		fault_create_debugfs_attr("fault", parent, &ibd->fault->attr);
	if (IS_ERR(fault_dir)) {
		kfree(ibd->fault);
		ibd->fault = NULL;
		return -ENOENT;
	}
	ibd->fault->dir = fault_dir;

	debugfs_create_file("fault_stats", 0444, fault_dir, ibd,
			    &_fault_stats_file_ops);
	debugfs_create_bool("enable", 0600, fault_dir, &ibd->fault->enable);
	debugfs_create_bool("suppress_err", 0600, fault_dir,
			    &ibd->fault->suppress_err);
	debugfs_create_bool("opcode_mode", 0600, fault_dir,
			    &ibd->fault->opcode);
	debugfs_create_file("opcodes", 0600, fault_dir, ibd->fault,
			    &__fault_opcodes_fops);
	debugfs_create_u64("skip_pkts", 0600, fault_dir,
			   &ibd->fault->fault_skip);
	debugfs_create_u64("skip_usec", 0600, fault_dir,
			   &ibd->fault->fault_skip_usec);
	debugfs_create_u8("direction", 0600, fault_dir, &ibd->fault->direction);

	return 0;
}