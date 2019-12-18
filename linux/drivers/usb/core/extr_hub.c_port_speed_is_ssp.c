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
typedef  int u32 ;
struct usb_ssp_cap_descriptor {int /*<<< orphan*/ * bmSublinkSpeedAttr; int /*<<< orphan*/  bmAttributes; } ;
struct usb_device {TYPE_1__* bos; } ;
struct TYPE_2__ {struct usb_ssp_cap_descriptor* ssp_cap; } ;

/* Variables and functions */
 int USB_SSP_SUBLINK_SPEED_ATTRIBS ; 
 int USB_SSP_SUBLINK_SPEED_LP ; 
 int USB_SSP_SUBLINK_SPEED_SSID ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int port_speed_is_ssp(struct usb_device *hdev, int speed_id)
{
	int ssa_count;
	u32 ss_attr;
	int i;
	struct usb_ssp_cap_descriptor *ssp_cap = hdev->bos->ssp_cap;

	if (!ssp_cap)
		return 0;

	ssa_count = le32_to_cpu(ssp_cap->bmAttributes) &
		USB_SSP_SUBLINK_SPEED_ATTRIBS;

	for (i = 0; i <= ssa_count; i++) {
		ss_attr = le32_to_cpu(ssp_cap->bmSublinkSpeedAttr[i]);
		if (speed_id == (ss_attr & USB_SSP_SUBLINK_SPEED_SSID))
			return !!(ss_attr & USB_SSP_SUBLINK_SPEED_LP);
	}
	return 0;
}