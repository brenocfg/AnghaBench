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

/* Variables and functions */
 int /*<<< orphan*/  crng_init_wait ; 
 int /*<<< orphan*/  crng_ready () ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 int wait_event_interruptible (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int wait_for_random_bytes(void)
{
	if (likely(crng_ready()))
		return 0;
	return wait_event_interruptible(crng_init_wait, crng_ready());
}