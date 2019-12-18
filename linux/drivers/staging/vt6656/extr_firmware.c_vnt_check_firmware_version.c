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
typedef  int /*<<< orphan*/  u8 ;
struct vnt_private {int firmware_version; TYPE_1__* usb; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int FIRMWARE_VERSION ; 
 int /*<<< orphan*/  MESSAGE_REQUEST_VERSION ; 
 int /*<<< orphan*/  MESSAGE_TYPE_READ ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,...) ; 
 int vnt_control_in (struct vnt_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int vnt_firmware_branch_to_sram (struct vnt_private*) ; 

int vnt_check_firmware_version(struct vnt_private *priv)
{
	int ret = 0;

	ret = vnt_control_in(priv, MESSAGE_TYPE_READ, 0,
			     MESSAGE_REQUEST_VERSION, 2,
			     (u8 *)&priv->firmware_version);
	if (ret) {
		dev_dbg(&priv->usb->dev,
			"Could not get firmware version: %d.\n", ret);
		goto end;
	}

	dev_dbg(&priv->usb->dev, "Firmware Version [%04x]\n",
		priv->firmware_version);

	if (priv->firmware_version == 0xFFFF) {
		dev_dbg(&priv->usb->dev, "In Loader.\n");
		ret = -EINVAL;
		goto end;
	}

	if (priv->firmware_version < FIRMWARE_VERSION) {
		/* branch to loader for download new firmware */
		ret = vnt_firmware_branch_to_sram(priv);
		if (ret) {
			dev_dbg(&priv->usb->dev,
				"Could not branch to SRAM: %d.\n", ret);
		} else {
			ret = -EINVAL;
		}
	}

end:
	return ret;
}