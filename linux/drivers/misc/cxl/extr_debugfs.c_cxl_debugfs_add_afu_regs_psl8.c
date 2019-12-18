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
struct cxl_afu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CXL_AFU_DEBUG_An ; 
 int /*<<< orphan*/  CXL_PSL_FIR_SLICE_An ; 
 int /*<<< orphan*/  CXL_PSL_SERR_An ; 
 int /*<<< orphan*/  CXL_PSL_SLICE_TRACE ; 
 int /*<<< orphan*/  CXL_SSTP0_An ; 
 int /*<<< orphan*/  CXL_SSTP1_An ; 
 int S_IRUSR ; 
 int S_IWUSR ; 
 int /*<<< orphan*/  _cxl_p1n_addr (struct cxl_afu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _cxl_p2n_addr (struct cxl_afu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugfs_create_io_x64 (char*,int,struct dentry*,int /*<<< orphan*/ ) ; 

void cxl_debugfs_add_afu_regs_psl8(struct cxl_afu *afu, struct dentry *dir)
{
	debugfs_create_io_x64("sstp0", S_IRUSR, dir, _cxl_p2n_addr(afu, CXL_SSTP0_An));
	debugfs_create_io_x64("sstp1", S_IRUSR, dir, _cxl_p2n_addr(afu, CXL_SSTP1_An));

	debugfs_create_io_x64("fir", S_IRUSR, dir, _cxl_p1n_addr(afu, CXL_PSL_FIR_SLICE_An));
	debugfs_create_io_x64("serr", S_IRUSR, dir, _cxl_p1n_addr(afu, CXL_PSL_SERR_An));
	debugfs_create_io_x64("afu_debug", S_IRUSR, dir, _cxl_p1n_addr(afu, CXL_AFU_DEBUG_An));
	debugfs_create_io_x64("trace", S_IRUSR | S_IWUSR, dir, _cxl_p1n_addr(afu, CXL_PSL_SLICE_TRACE));
}