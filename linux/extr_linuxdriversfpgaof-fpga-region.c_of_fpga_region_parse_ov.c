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
struct device {int dummy; } ;
struct fpga_region {scalar_t__ info; struct device dev; } ;
struct fpga_image_info {int flags; int /*<<< orphan*/  firmware_name; int /*<<< orphan*/  config_complete_timeout_us; int /*<<< orphan*/  disable_timeout_us; int /*<<< orphan*/  enable_timeout_us; struct device_node* overlay; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 struct fpga_image_info* ERR_PTR (int) ; 
 int FPGA_MGR_ENCRYPTED_BITSTREAM ; 
 int FPGA_MGR_EXTERNAL_CONFIG ; 
 int FPGA_MGR_PARTIAL_RECONFIG ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int child_regions_with_firmware (struct device_node*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  devm_kstrdup (struct device*,char const*,int /*<<< orphan*/ ) ; 
 struct fpga_image_info* fpga_image_info_alloc (struct device*) ; 
 int /*<<< orphan*/  fpga_image_info_free (struct fpga_image_info*) ; 
 scalar_t__ of_property_read_bool (struct device_node*,char*) ; 
 int /*<<< orphan*/  of_property_read_string (struct device_node*,char*,char const**) ; 
 int /*<<< orphan*/  of_property_read_u32 (struct device_node*,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct fpga_image_info *of_fpga_region_parse_ov(
						struct fpga_region *region,
						struct device_node *overlay)
{
	struct device *dev = &region->dev;
	struct fpga_image_info *info;
	const char *firmware_name;
	int ret;

	if (region->info) {
		dev_err(dev, "Region already has overlay applied.\n");
		return ERR_PTR(-EINVAL);
	}

	/*
	 * Reject overlay if child FPGA Regions added in the overlay have
	 * firmware-name property (would mean that an FPGA region that has
	 * not been added to the live tree yet is doing FPGA programming).
	 */
	ret = child_regions_with_firmware(overlay);
	if (ret)
		return ERR_PTR(ret);

	info = fpga_image_info_alloc(dev);
	if (!info)
		return ERR_PTR(-ENOMEM);

	info->overlay = overlay;

	/* Read FPGA region properties from the overlay */
	if (of_property_read_bool(overlay, "partial-fpga-config"))
		info->flags |= FPGA_MGR_PARTIAL_RECONFIG;

	if (of_property_read_bool(overlay, "external-fpga-config"))
		info->flags |= FPGA_MGR_EXTERNAL_CONFIG;

	if (of_property_read_bool(overlay, "encrypted-fpga-config"))
		info->flags |= FPGA_MGR_ENCRYPTED_BITSTREAM;

	if (!of_property_read_string(overlay, "firmware-name",
				     &firmware_name)) {
		info->firmware_name = devm_kstrdup(dev, firmware_name,
						   GFP_KERNEL);
		if (!info->firmware_name)
			return ERR_PTR(-ENOMEM);
	}

	of_property_read_u32(overlay, "region-unfreeze-timeout-us",
			     &info->enable_timeout_us);

	of_property_read_u32(overlay, "region-freeze-timeout-us",
			     &info->disable_timeout_us);

	of_property_read_u32(overlay, "config-complete-timeout-us",
			     &info->config_complete_timeout_us);

	/* If overlay is not programming the FPGA, don't need FPGA image info */
	if (!info->firmware_name) {
		ret = 0;
		goto ret_no_info;
	}

	/*
	 * If overlay informs us FPGA was externally programmed, specifying
	 * firmware here would be ambiguous.
	 */
	if (info->flags & FPGA_MGR_EXTERNAL_CONFIG) {
		dev_err(dev, "error: specified firmware and external-fpga-config");
		ret = -EINVAL;
		goto ret_no_info;
	}

	return info;
ret_no_info:
	fpga_image_info_free(info);
	return ERR_PTR(ret);
}