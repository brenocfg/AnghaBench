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
struct urb {scalar_t__ context; } ;
struct completion {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  complete (struct completion*) ; 

__attribute__((used)) static void vub300_usb_bulk_msg_completion(struct urb *urb)
{				/* urb completion handler - hardirq */
	complete((struct completion *)urb->context);
}