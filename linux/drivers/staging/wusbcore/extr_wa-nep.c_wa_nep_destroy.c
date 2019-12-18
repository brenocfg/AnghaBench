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
struct wahc {int /*<<< orphan*/  nep_buffer; int /*<<< orphan*/  nep_urb; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_free_urb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wa_nep_disarm (struct wahc*) ; 

void wa_nep_destroy(struct wahc *wa)
{
	wa_nep_disarm(wa);
	usb_free_urb(wa->nep_urb);
	kfree(wa->nep_buffer);
}