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
struct rt2x00_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  REGISTER_TIMEOUT ; 
 int /*<<< orphan*/  USB_RX_CONTROL ; 
 int /*<<< orphan*/  rt2x00usb_vendor_request_sw (struct rt2x00_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void rt2x00usb_disable_radio(struct rt2x00_dev *rt2x00dev)
{
	rt2x00usb_vendor_request_sw(rt2x00dev, USB_RX_CONTROL, 0, 0,
				    REGISTER_TIMEOUT);
}