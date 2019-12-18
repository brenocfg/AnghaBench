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
struct wahc {int /*<<< orphan*/  dti_buf; scalar_t__ dti_urb; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_kill_urb (scalar_t__) ; 
 int /*<<< orphan*/  usb_put_urb (scalar_t__) ; 
 int /*<<< orphan*/  wa_nep_destroy (struct wahc*) ; 
 int /*<<< orphan*/  wa_rpipes_destroy (struct wahc*) ; 

void __wa_destroy(struct wahc *wa)
{
	if (wa->dti_urb) {
		usb_kill_urb(wa->dti_urb);
		usb_put_urb(wa->dti_urb);
	}
	kfree(wa->dti_buf);
	wa_nep_destroy(wa);
	wa_rpipes_destroy(wa);
}