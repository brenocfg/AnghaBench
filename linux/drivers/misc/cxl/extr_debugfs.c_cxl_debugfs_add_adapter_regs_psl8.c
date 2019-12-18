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
struct dentry {int dummy; } ;
struct cxl {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CXL_PSL_FIR1 ; 
 int /*<<< orphan*/  CXL_PSL_FIR2 ; 
 int /*<<< orphan*/  CXL_PSL_FIR_CNTL ; 
 int /*<<< orphan*/  CXL_PSL_TRACE ; 
 int S_IRUSR ; 
 int S_IWUSR ; 
 int /*<<< orphan*/  _cxl_p1_addr (struct cxl*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugfs_create_io_x64 (char*,int,struct dentry*,int /*<<< orphan*/ ) ; 

void cxl_debugfs_add_adapter_regs_psl8(struct cxl *adapter, struct dentry *dir)
{
	debugfs_create_io_x64("fir1", S_IRUSR, dir, _cxl_p1_addr(adapter, CXL_PSL_FIR1));
	debugfs_create_io_x64("fir2", S_IRUSR, dir, _cxl_p1_addr(adapter, CXL_PSL_FIR2));
	debugfs_create_io_x64("fir_cntl", S_IRUSR, dir, _cxl_p1_addr(adapter, CXL_PSL_FIR_CNTL));
	debugfs_create_io_x64("trace", S_IRUSR | S_IWUSR, dir, _cxl_p1_addr(adapter, CXL_PSL_TRACE));
}