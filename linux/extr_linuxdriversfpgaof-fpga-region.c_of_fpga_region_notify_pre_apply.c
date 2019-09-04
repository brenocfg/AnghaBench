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
struct of_overlay_notify_data {int /*<<< orphan*/  overlay; } ;
struct device {int dummy; } ;
struct fpga_region {struct fpga_image_info* info; struct device dev; } ;
struct fpga_image_info {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IS_ERR (struct fpga_image_info*) ; 
 int PTR_ERR (struct fpga_image_info*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  fpga_image_info_free (struct fpga_image_info*) ; 
 int fpga_region_program_fpga (struct fpga_region*) ; 
 struct fpga_image_info* of_fpga_region_parse_ov (struct fpga_region*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int of_fpga_region_notify_pre_apply(struct fpga_region *region,
					   struct of_overlay_notify_data *nd)
{
	struct device *dev = &region->dev;
	struct fpga_image_info *info;
	int ret;

	info = of_fpga_region_parse_ov(region, nd->overlay);
	if (IS_ERR(info))
		return PTR_ERR(info);

	/* If overlay doesn't program the FPGA, accept it anyway. */
	if (!info)
		return 0;

	if (region->info) {
		dev_err(dev, "Region already has overlay applied.\n");
		return -EINVAL;
	}

	region->info = info;
	ret = fpga_region_program_fpga(region);
	if (ret) {
		/* error; reject overlay */
		fpga_image_info_free(info);
		region->info = NULL;
	}

	return ret;
}