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
typedef  int u16 ;

/* Variables and functions */
#define  TEST_FORCE_EN 132 
#define  TEST_J 131 
#define  TEST_K 130 
#define  TEST_PACKET 129 
#define  TEST_SE0_NAK 128 

__attribute__((used)) static const char *usb_decode_test_mode(u16 wIndex)
{
	switch (wIndex) {
	case TEST_J:
		return ": TEST_J";
	case TEST_K:
		return ": TEST_K";
	case TEST_SE0_NAK:
		return ": TEST_SE0_NAK";
	case TEST_PACKET:
		return ": TEST_PACKET";
	case TEST_FORCE_EN:
		return ": TEST_FORCE_EN";
	default:
		return ": UNKNOWN";
	}
}