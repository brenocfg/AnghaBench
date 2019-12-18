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
struct usb_hcd {int dummy; } ;
struct max3421_hcd {int port_status; int /*<<< orphan*/  spi_thread; int /*<<< orphan*/  todo; } ;

/* Variables and functions */
 int /*<<< orphan*/  RESET_PORT ; 
 int USB_PORT_STAT_ENABLE ; 
 int USB_PORT_STAT_LOW_SPEED ; 
 int USB_PORT_STAT_RESET ; 
 struct max3421_hcd* hcd_to_max3421 (struct usb_hcd*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_process (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
max3421_reset_port(struct usb_hcd *hcd)
{
	struct max3421_hcd *max3421_hcd = hcd_to_max3421(hcd);

	max3421_hcd->port_status &= ~(USB_PORT_STAT_ENABLE |
				      USB_PORT_STAT_LOW_SPEED);
	max3421_hcd->port_status |= USB_PORT_STAT_RESET;
	set_bit(RESET_PORT, &max3421_hcd->todo);
	wake_up_process(max3421_hcd->spi_thread);
	return 0;
}