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
struct urb {int transfer_flags; struct urb* transfer_buffer; } ;
struct kref {int dummy; } ;

/* Variables and functions */
 int URB_FREE_BUFFER ; 
 int /*<<< orphan*/  kfree (struct urb*) ; 
 struct urb* to_urb (struct kref*) ; 

__attribute__((used)) static void urb_destroy(struct kref *kref)
{
	struct urb *urb = to_urb(kref);

	if (urb->transfer_flags & URB_FREE_BUFFER)
		kfree(urb->transfer_buffer);

	kfree(urb);
}