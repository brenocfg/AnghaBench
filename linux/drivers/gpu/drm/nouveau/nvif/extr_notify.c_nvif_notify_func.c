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
struct nvif_notify {int (* func ) (struct nvif_notify*) ;int /*<<< orphan*/  putcnt; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int NVIF_NOTIFY_KEEP ; 
 int /*<<< orphan*/  NVIF_NOTIFY_USER ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvif_notify_get_ (struct nvif_notify*) ; 
 int stub1 (struct nvif_notify*) ; 
 int /*<<< orphan*/  test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int
nvif_notify_func(struct nvif_notify *notify, bool keep)
{
	int ret = notify->func(notify);
	if (ret == NVIF_NOTIFY_KEEP ||
	    !test_and_clear_bit(NVIF_NOTIFY_USER, &notify->flags)) {
		if (!keep)
			atomic_dec(&notify->putcnt);
		else
			nvif_notify_get_(notify);
	}
	return ret;
}