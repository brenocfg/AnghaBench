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

__attribute__((used)) static inline void disable_surveillance(void)
{
#ifdef CONFIG_PPC_PSERIES
	/* Since this can't be a module, args should end up below 4GB. */
	static struct rtas_args args;

	/*
	 * At this point we have got all the cpus we can into
	 * xmon, so there is hopefully no other cpu calling RTAS
	 * at the moment, even though we don't take rtas.lock.
	 * If we did try to take rtas.lock there would be a
	 * real possibility of deadlock.
	 */
	if (set_indicator_token == RTAS_UNKNOWN_SERVICE)
		return;

	rtas_call_unlocked(&args, set_indicator_token, 3, 1, NULL,
			   SURVEILLANCE_TOKEN, 0, 0);

#endif /* CONFIG_PPC_PSERIES */
}