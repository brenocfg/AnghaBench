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
struct TYPE_2__ {int /*<<< orphan*/  proposed_mac; } ;
struct flexcop_device {TYPE_1__ dvb_adapter; int /*<<< orphan*/  bus_specific; } ;

/* Variables and functions */
 int /*<<< orphan*/  B2C2_USB_READ_V8_MEM ; 
 int /*<<< orphan*/  V8_MEMORY_PAGE_FLASH ; 
 int flexcop_usb_memory_req (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int flexcop_usb_get_mac_addr(struct flexcop_device *fc, int extended)
{
	return flexcop_usb_memory_req(fc->bus_specific, B2C2_USB_READ_V8_MEM,
		V8_MEMORY_PAGE_FLASH, 0x1f010, 1,
		fc->dvb_adapter.proposed_mac, 6);
}