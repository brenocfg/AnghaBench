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
struct urb {int dummy; } ;
struct es2_ap_dev {struct urb** arpc_urb; } ;

/* Variables and functions */
 int NUM_ARPC_IN_URB ; 
 int /*<<< orphan*/  usb_kill_urb (struct urb*) ; 

__attribute__((used)) static void es2_arpc_in_disable(struct es2_ap_dev *es2)
{
	struct urb *urb;
	int i;

	for (i = 0; i < NUM_ARPC_IN_URB; ++i) {
		urb = es2->arpc_urb[i];
		usb_kill_urb(urb);
	}
}