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
struct wahc {int /*<<< orphan*/  nep_buffer_size; int /*<<< orphan*/  nep_buffer; struct urb* nep_urb; } ;
struct urb {int /*<<< orphan*/  transfer_buffer_length; int /*<<< orphan*/  transfer_buffer; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int usb_submit_urb (struct urb*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int wa_nep_arm(struct wahc *wa, gfp_t gfp_mask)
{
	struct urb *urb = wa->nep_urb;
	urb->transfer_buffer = wa->nep_buffer;
	urb->transfer_buffer_length = wa->nep_buffer_size;
	return usb_submit_urb(urb, gfp_mask);
}