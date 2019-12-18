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
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct dentry {int dummy; } ;
struct cxl_afu {int slice; TYPE_3__* adapter; struct dentry* debugfs; } ;
struct TYPE_6__ {int adapter_num; TYPE_2__* native; int /*<<< orphan*/  debugfs; } ;
struct TYPE_5__ {TYPE_1__* sl_ops; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* debugfs_add_afu_regs ) (struct cxl_afu*,struct dentry*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CXL_PSL_DAR_An ; 
 int /*<<< orphan*/  CXL_PSL_DSISR_An ; 
 int /*<<< orphan*/  CXL_PSL_ErrStat_An ; 
 int /*<<< orphan*/  CXL_PSL_SR_An ; 
 int /*<<< orphan*/  S_IRUSR ; 
 int /*<<< orphan*/  _cxl_p1n_addr (struct cxl_afu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _cxl_p2n_addr (struct cxl_afu*,int /*<<< orphan*/ ) ; 
 struct dentry* debugfs_create_dir (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugfs_create_io_x64 (char*,int /*<<< orphan*/ ,struct dentry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int,int) ; 
 int /*<<< orphan*/  stub1 (struct cxl_afu*,struct dentry*) ; 

void cxl_debugfs_afu_add(struct cxl_afu *afu)
{
	struct dentry *dir;
	char buf[32];

	if (!afu->adapter->debugfs)
		return;

	snprintf(buf, 32, "psl%i.%i", afu->adapter->adapter_num, afu->slice);
	dir = debugfs_create_dir(buf, afu->adapter->debugfs);
	afu->debugfs = dir;

	debugfs_create_io_x64("sr",         S_IRUSR, dir, _cxl_p1n_addr(afu, CXL_PSL_SR_An));
	debugfs_create_io_x64("dsisr",      S_IRUSR, dir, _cxl_p2n_addr(afu, CXL_PSL_DSISR_An));
	debugfs_create_io_x64("dar",        S_IRUSR, dir, _cxl_p2n_addr(afu, CXL_PSL_DAR_An));

	debugfs_create_io_x64("err_status", S_IRUSR, dir, _cxl_p2n_addr(afu, CXL_PSL_ErrStat_An));

	if (afu->adapter->native->sl_ops->debugfs_add_afu_regs)
		afu->adapter->native->sl_ops->debugfs_add_afu_regs(afu, dir);
}