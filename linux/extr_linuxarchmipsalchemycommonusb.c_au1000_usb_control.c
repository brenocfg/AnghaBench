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

/* Variables and functions */
#define  ALCHEMY_USB_OHCI0 128 
 int ENODEV ; 
 int /*<<< orphan*/  __au1xx0_ohci_control (int,unsigned long,int) ; 

__attribute__((used)) static inline int au1000_usb_control(int block, int enable, unsigned long rb,
				     int creg)
{
	int ret = 0;

	switch (block) {
	case ALCHEMY_USB_OHCI0:
		__au1xx0_ohci_control(enable, rb, creg);
		break;
	default:
		ret = -ENODEV;
	}
	return ret;
}