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
struct sh_sleep_data {int dummy; } ;

/* Variables and functions */
 unsigned long RAM_BASE ; 
 unsigned long SUSP_SH_MMU ; 
 int /*<<< orphan*/  atomic_notifier_call_chain (int /*<<< orphan*/ *,unsigned long,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flush_cache_all () ; 
 int /*<<< orphan*/  sh_mobile_post_sleep_notifier_list ; 
 int /*<<< orphan*/  sh_mobile_pre_sleep_notifier_list ; 

void sh_mobile_call_standby(unsigned long mode)
{
	void *onchip_mem = (void *)RAM_BASE;
	struct sh_sleep_data *sdp = onchip_mem;
	void (*standby_onchip_mem)(unsigned long, unsigned long);

	/* code located directly after data structure */
	standby_onchip_mem = (void *)(sdp + 1);

	atomic_notifier_call_chain(&sh_mobile_pre_sleep_notifier_list,
				   mode, NULL);

	/* flush the caches if MMU flag is set */
	if (mode & SUSP_SH_MMU)
		flush_cache_all();

	/* Let assembly snippet in on-chip memory handle the rest */
	standby_onchip_mem(mode, RAM_BASE);

	atomic_notifier_call_chain(&sh_mobile_post_sleep_notifier_list,
				   mode, NULL);
}