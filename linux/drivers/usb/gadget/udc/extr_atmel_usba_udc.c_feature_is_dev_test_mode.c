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
struct usb_ctrlrequest {scalar_t__ wValue; } ;

/* Variables and functions */
 int /*<<< orphan*/  USB_DEVICE_TEST_MODE ; 
 scalar_t__ cpu_to_le16 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool feature_is_dev_test_mode(struct usb_ctrlrequest *crq)
{
	if (crq->wValue == cpu_to_le16(USB_DEVICE_TEST_MODE))
		return true;
	return false;
}