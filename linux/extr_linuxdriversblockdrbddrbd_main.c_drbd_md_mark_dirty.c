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
struct drbd_device {int /*<<< orphan*/  md_sync_timer; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  MD_DIRTY ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void drbd_md_mark_dirty(struct drbd_device *device)
{
	if (!test_and_set_bit(MD_DIRTY, &device->flags))
		mod_timer(&device->md_sync_timer, jiffies + 5*HZ);
}