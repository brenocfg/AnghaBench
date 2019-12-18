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
struct urb {int /*<<< orphan*/  transfer_buffer; int /*<<< orphan*/  setup_packet; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void usbctrl_async_callback(struct urb *urb)
{
	if (urb) {
		/* free dr */
		kfree(urb->setup_packet);
		/* free databuf */
		kfree(urb->transfer_buffer);
	}
}