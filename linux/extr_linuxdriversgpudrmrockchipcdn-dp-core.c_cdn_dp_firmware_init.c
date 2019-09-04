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
typedef  int /*<<< orphan*/  u32 ;
struct firmware {scalar_t__ size; scalar_t__ data; } ;
struct cdn_firmware_header {int /*<<< orphan*/  dram_size; scalar_t__ iram_size; scalar_t__ header_size; int /*<<< orphan*/  size_bytes; } ;
struct cdn_dp_device {int /*<<< orphan*/  dev; struct firmware* fw; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEV_ERROR (int /*<<< orphan*/ ,char*,...) ; 
 int EINVAL ; 
 int cdn_dp_event_config (struct cdn_dp_device*) ; 
 int cdn_dp_load_firmware (struct cdn_dp_device*,int /*<<< orphan*/  const*,scalar_t__,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int cdn_dp_set_firmware_active (struct cdn_dp_device*,int) ; 
 scalar_t__ le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cdn_dp_firmware_init(struct cdn_dp_device *dp)
{
	int ret;
	const u32 *iram_data, *dram_data;
	const struct firmware *fw = dp->fw;
	const struct cdn_firmware_header *hdr;

	hdr = (struct cdn_firmware_header *)fw->data;
	if (fw->size != le32_to_cpu(hdr->size_bytes)) {
		DRM_DEV_ERROR(dp->dev, "firmware is invalid\n");
		return -EINVAL;
	}

	iram_data = (const u32 *)(fw->data + hdr->header_size);
	dram_data = (const u32 *)(fw->data + hdr->header_size + hdr->iram_size);

	ret = cdn_dp_load_firmware(dp, iram_data, hdr->iram_size,
				   dram_data, hdr->dram_size);
	if (ret)
		return ret;

	ret = cdn_dp_set_firmware_active(dp, true);
	if (ret) {
		DRM_DEV_ERROR(dp->dev, "active ucpu failed: %d\n", ret);
		return ret;
	}

	return cdn_dp_event_config(dp);
}