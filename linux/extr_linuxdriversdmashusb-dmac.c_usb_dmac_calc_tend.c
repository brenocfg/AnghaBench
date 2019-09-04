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
typedef  int u32 ;

/* Variables and functions */
 int USB_DMAC_XFER_SIZE ; 

__attribute__((used)) static u32 usb_dmac_calc_tend(u32 size)
{
	/*
	 * Please refer to the Figure "Example of Final Transaction Valid
	 * Data Transfer Enable (EDTEN) Setting" in the data sheet.
	 */
	return 0xffffffff << (32 - (size % USB_DMAC_XFER_SIZE ?	:
						USB_DMAC_XFER_SIZE));
}