#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct r8152 {int /*<<< orphan*/  flags; TYPE_1__* udev; } ;
struct TYPE_2__ {scalar_t__ state; } ;

/* Variables and functions */
 int /*<<< orphan*/  RTL8152_UNPLUG ; 
 scalar_t__ USB_STATE_NOTATTACHED ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_mb__after_atomic () ; 

__attribute__((used)) static void rtl_set_unplug(struct r8152 *tp)
{
	if (tp->udev->state == USB_STATE_NOTATTACHED) {
		set_bit(RTL8152_UNPLUG, &tp->flags);
		smp_mb__after_atomic();
	}
}