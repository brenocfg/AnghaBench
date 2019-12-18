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
struct firmware {scalar_t__ size; scalar_t__ data; } ;
struct drm_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_hdcp_srm_update (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  release_firmware (struct firmware const*) ; 
 int request_firmware_direct (struct firmware const**,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void drm_hdcp_request_srm(struct drm_device *drm_dev)
{
	char fw_name[36] = "display_hdcp_srm.bin";
	const struct firmware *fw;

	int ret;

	ret = request_firmware_direct(&fw, (const char *)fw_name,
				      drm_dev->dev);
	if (ret < 0)
		goto exit;

	if (fw->size && fw->data)
		drm_hdcp_srm_update(fw->data, fw->size);

exit:
	release_firmware(fw);
}