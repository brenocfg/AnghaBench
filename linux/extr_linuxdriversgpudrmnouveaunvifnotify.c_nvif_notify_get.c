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
struct nvif_notify {int /*<<< orphan*/  flags; int /*<<< orphan*/  object; } ;

/* Variables and functions */
 int /*<<< orphan*/  NVIF_NOTIFY_USER ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 int nvif_notify_get_ (struct nvif_notify*) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int
nvif_notify_get(struct nvif_notify *notify)
{
	if (likely(notify->object) &&
	    !test_and_set_bit(NVIF_NOTIFY_USER, &notify->flags))
		return nvif_notify_get_(notify);
	return 0;
}