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
struct dwc3 {int test_mode_nr; int test_mode; } ;
typedef  enum usb_device_state { ____Placeholder_usb_device_state } usb_device_state ;

/* Variables and functions */
 int EINVAL ; 
#define  TEST_FORCE_EN 132 
#define  TEST_J 131 
#define  TEST_K 130 
#define  TEST_PACKET 129 
#define  TEST_SE0_NAK 128 

__attribute__((used)) static int dwc3_ep0_handle_test(struct dwc3 *dwc, enum usb_device_state state,
		u32 wIndex, int set)
{
	if ((wIndex & 0xff) != 0)
		return -EINVAL;
	if (!set)
		return -EINVAL;

	switch (wIndex >> 8) {
	case TEST_J:
	case TEST_K:
	case TEST_SE0_NAK:
	case TEST_PACKET:
	case TEST_FORCE_EN:
		dwc->test_mode_nr = wIndex >> 8;
		dwc->test_mode = true;
		break;
	default:
		return -EINVAL;
	}

	return 0;
}