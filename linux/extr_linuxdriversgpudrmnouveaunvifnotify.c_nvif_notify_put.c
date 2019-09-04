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
struct nvif_notify {int /*<<< orphan*/  work; int /*<<< orphan*/  flags; int /*<<< orphan*/  object; } ;

/* Variables and functions */
 int /*<<< orphan*/  NVIF_NOTIFY_USER ; 
 int /*<<< orphan*/  NVIF_NOTIFY_WORK ; 
 int /*<<< orphan*/  flush_work (int /*<<< orphan*/ *) ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 int nvif_notify_put_ (struct nvif_notify*) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int
nvif_notify_put(struct nvif_notify *notify)
{
	if (likely(notify->object) &&
	    test_and_clear_bit(NVIF_NOTIFY_USER, &notify->flags)) {
		int ret = nvif_notify_put_(notify);
		if (test_bit(NVIF_NOTIFY_WORK, &notify->flags))
			flush_work(&notify->work);
		return ret;
	}
	return 0;
}