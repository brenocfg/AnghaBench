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
struct TYPE_2__ {int (* write_complete ) (struct fpga_manager*,struct fpga_image_info*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  FPGA_MGR_STATE_OPERATING ; 
 int /*<<< orphan*/  FPGA_MGR_STATE_WRITE_COMPLETE ; 
 int /*<<< orphan*/  FPGA_MGR_STATE_WRITE_COMPLETE_ERR ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int stub1 (struct fpga_manager*,struct fpga_image_info*) ; 

__attribute__((used)) static int fpga_mgr_write_complete(struct fpga_manager *mgr,
				   struct fpga_image_info *info)
{
	int ret;

	mgr->state = FPGA_MGR_STATE_WRITE_COMPLETE;
	ret = mgr->mops->write_complete(mgr, info);
	if (ret) {
		dev_err(&mgr->dev, "Error after writing image data to FPGA\n");
		mgr->state = FPGA_MGR_STATE_WRITE_COMPLETE_ERR;
		return ret;
	}
	mgr->state = FPGA_MGR_STATE_OPERATING;

	return 0;
}