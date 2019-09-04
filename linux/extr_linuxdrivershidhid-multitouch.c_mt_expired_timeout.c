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
struct timer_list {int dummy; } ;
struct mt_device {int /*<<< orphan*/  mt_io_flags; struct hid_device* hdev; } ;
struct hid_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MT_IO_FLAGS_PENDING_SLOTS ; 
 int /*<<< orphan*/  MT_IO_FLAGS_RUNNING ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct mt_device* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt_release_contacts (struct hid_device*) ; 
 int /*<<< orphan*/  release_timer ; 
 struct mt_device* td ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mt_expired_timeout(struct timer_list *t)
{
	struct mt_device *td = from_timer(td, t, release_timer);
	struct hid_device *hdev = td->hdev;

	/*
	 * An input report came in just before we release the sticky fingers,
	 * it will take care of the sticky fingers.
	 */
	if (test_and_set_bit(MT_IO_FLAGS_RUNNING, &td->mt_io_flags))
		return;
	if (test_bit(MT_IO_FLAGS_PENDING_SLOTS, &td->mt_io_flags))
		mt_release_contacts(hdev);
	clear_bit(MT_IO_FLAGS_RUNNING, &td->mt_io_flags);
}