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
struct spufs_calls {int /*<<< orphan*/  (* notify_spus_active ) () ;} ;

/* Variables and functions */
 struct spufs_calls* spufs_calls_get () ; 
 int /*<<< orphan*/  spufs_calls_put (struct spufs_calls*) ; 
 int /*<<< orphan*/  stub1 () ; 

void notify_spus_active(void)
{
	struct spufs_calls *calls;

	calls = spufs_calls_get();
	if (!calls)
		return;

	calls->notify_spus_active();
	spufs_calls_put(calls);

	return;
}