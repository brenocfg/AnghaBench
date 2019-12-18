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
typedef  int u8 ;
struct usb_hcd {int dummy; } ;
struct max3421_hcd {int* iopins; int /*<<< orphan*/  spi_thread; int /*<<< orphan*/  todo; } ;

/* Variables and functions */
 int /*<<< orphan*/  IOPIN_UPDATE ; 
 int MAX3421_GPOUT_COUNT ; 
 struct max3421_hcd* hcd_to_max3421 (struct usb_hcd*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_process (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
max3421_gpout_set_value(struct usb_hcd *hcd, u8 pin_number, u8 value)
{
	struct max3421_hcd *max3421_hcd = hcd_to_max3421(hcd);
	u8 mask, idx;

	--pin_number;
	if (pin_number >= MAX3421_GPOUT_COUNT)
		return;

	mask = 1u << (pin_number % 4);
	idx = pin_number / 4;

	if (value)
		max3421_hcd->iopins[idx] |=  mask;
	else
		max3421_hcd->iopins[idx] &= ~mask;
	set_bit(IOPIN_UPDATE, &max3421_hcd->todo);
	wake_up_process(max3421_hcd->spi_thread);
}