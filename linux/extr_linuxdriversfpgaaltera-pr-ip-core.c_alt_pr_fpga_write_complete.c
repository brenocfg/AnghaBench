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
typedef  scalar_t__ u32 ;
struct fpga_manager {int /*<<< orphan*/  dev; } ;
struct fpga_image_info {scalar_t__ config_complete_timeout_us; } ;

/* Variables and functions */
 int EIO ; 
 int ETIMEDOUT ; 
#define  FPGA_MGR_STATE_OPERATING 129 
#define  FPGA_MGR_STATE_WRITE_ERR 128 
 int alt_pr_fpga_state (struct fpga_manager*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int alt_pr_fpga_write_complete(struct fpga_manager *mgr,
				      struct fpga_image_info *info)
{
	u32 i = 0;

	do {
		switch (alt_pr_fpga_state(mgr)) {
		case FPGA_MGR_STATE_WRITE_ERR:
			return -EIO;

		case FPGA_MGR_STATE_OPERATING:
			dev_info(&mgr->dev,
				 "successful partial reconfiguration\n");
			return 0;

		default:
			break;
		}
		udelay(1);
	} while (info->config_complete_timeout_us > i++);

	dev_err(&mgr->dev, "timed out waiting for write to complete\n");
	return -ETIMEDOUT;
}