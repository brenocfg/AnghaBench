#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct device {int dummy; } ;
struct TYPE_4__ {TYPE_1__* pusbdev; } ;
struct _adapter {int /*<<< orphan*/  rtl8712_fw_ready; TYPE_2__ dvobjpriv; } ;
struct TYPE_3__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  firmware_file ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int request_firmware_nowait (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct device*,int /*<<< orphan*/ ,struct _adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl871x_load_fw_cb ; 

int rtl871x_load_fw(struct _adapter *padapter)
{
	struct device *dev = &padapter->dvobjpriv.pusbdev->dev;
	int rc;

	init_completion(&padapter->rtl8712_fw_ready);
	dev_info(dev, "r8712u: Loading firmware from \"%s\"\n", firmware_file);
	rc = request_firmware_nowait(THIS_MODULE, 1, firmware_file, dev,
				     GFP_KERNEL, padapter, rtl871x_load_fw_cb);
	if (rc)
		dev_err(dev, "r8712u: Firmware request error %d\n", rc);
	return rc;
}