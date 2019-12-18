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
struct TYPE_4__ {int bHubHdrDecLat; scalar_t__ DeviceRemovable; } ;
struct TYPE_3__ {TYPE_2__ ss; } ;
struct usb_hub_descriptor {int bDescLength; int bNbrPorts; TYPE_1__ u; int /*<<< orphan*/  wHubCharacteristics; int /*<<< orphan*/  bDescriptorType; } ;

/* Variables and functions */
 int HUB_CHAR_COMMON_OCPM ; 
 int HUB_CHAR_INDV_PORT_LPSM ; 
 int /*<<< orphan*/  USB_DT_SS_HUB ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 int /*<<< orphan*/  memset (struct usb_hub_descriptor*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void
ss_hub_descriptor(struct usb_hub_descriptor *desc)
{
	memset(desc, 0, sizeof *desc);
	desc->bDescriptorType = USB_DT_SS_HUB;
	desc->bDescLength = 12;
	desc->wHubCharacteristics = cpu_to_le16(
			HUB_CHAR_INDV_PORT_LPSM |
			HUB_CHAR_COMMON_OCPM);
	desc->bNbrPorts = 1;
	desc->u.ss.bHubHdrDecLat = 0x04; /* Worst case: 0.4 micro sec*/
	desc->u.ss.DeviceRemovable = 0;
}