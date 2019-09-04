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
struct sony_sc {int /*<<< orphan*/  state_worker; scalar_t__ state_worker_initialized; int /*<<< orphan*/  hotplug_worker; scalar_t__ hotplug_worker_initialized; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void sony_cancel_work_sync(struct sony_sc *sc)
{
	if (sc->hotplug_worker_initialized)
		cancel_work_sync(&sc->hotplug_worker);
	if (sc->state_worker_initialized)
		cancel_work_sync(&sc->state_worker);
}