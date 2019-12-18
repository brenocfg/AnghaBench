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
struct es2_cport_in {struct urb** urb; } ;
struct es2_ap_dev {int dummy; } ;

/* Variables and functions */
 int NUM_CPORT_IN_URB ; 
 int /*<<< orphan*/  usb_kill_urb (struct urb*) ; 

__attribute__((used)) static void es2_cport_in_disable(struct es2_ap_dev *es2,
				 struct es2_cport_in *cport_in)
{
	struct urb *urb;
	int i;

	for (i = 0; i < NUM_CPORT_IN_URB; ++i) {
		urb = cport_in->urb[i];
		usb_kill_urb(urb);
	}
}