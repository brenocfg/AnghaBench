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
struct drbd_device {int /*<<< orphan*/  misc_wait; } ;

/* Variables and functions */
 int /*<<< orphan*/  inc_ap_bio_cond (struct drbd_device*) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void inc_ap_bio(struct drbd_device *device)
{
	/* we wait here
	 *    as long as the device is suspended
	 *    until the bitmap is no longer on the fly during connection
	 *    handshake as long as we would exceed the max_buffer limit.
	 *
	 * to avoid races with the reconnect code,
	 * we need to atomic_inc within the spinlock. */

	wait_event(device->misc_wait, inc_ap_bio_cond(device));
}