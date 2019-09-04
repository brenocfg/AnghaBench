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
struct fpga_manager {int /*<<< orphan*/  state; int /*<<< orphan*/  dev; TYPE_1__* mops; } ;
struct fpga_image_info {int dummy; } ;
struct TYPE_2__ {int (* write ) (struct fpga_manager*,char const*,size_t) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  FPGA_MGR_STATE_WRITE ; 
 int /*<<< orphan*/  FPGA_MGR_STATE_WRITE_ERR ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int fpga_mgr_write_complete (struct fpga_manager*,struct fpga_image_info*) ; 
 int fpga_mgr_write_init_buf (struct fpga_manager*,struct fpga_image_info*,char const*,size_t) ; 
 int stub1 (struct fpga_manager*,char const*,size_t) ; 

__attribute__((used)) static int fpga_mgr_buf_load_mapped(struct fpga_manager *mgr,
				    struct fpga_image_info *info,
				    const char *buf, size_t count)
{
	int ret;

	ret = fpga_mgr_write_init_buf(mgr, info, buf, count);
	if (ret)
		return ret;

	/*
	 * Write the FPGA image to the FPGA.
	 */
	mgr->state = FPGA_MGR_STATE_WRITE;
	ret = mgr->mops->write(mgr, buf, count);
	if (ret) {
		dev_err(&mgr->dev, "Error while writing image data to FPGA\n");
		mgr->state = FPGA_MGR_STATE_WRITE_ERR;
		return ret;
	}

	return fpga_mgr_write_complete(mgr, info);
}