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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int /*<<< orphan*/  __pa (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flush_cache_all () ; 
 int /*<<< orphan*/  omap_smc2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outer_clean_range (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

u32 omap_secure_dispatcher(u32 idx, u32 flag, u32 nargs, u32 arg1, u32 arg2,
							 u32 arg3, u32 arg4)
{
	u32 ret;
	u32 param[5];

	param[0] = nargs;
	param[1] = arg1;
	param[2] = arg2;
	param[3] = arg3;
	param[4] = arg4;

	/*
	 * Secure API needs physical address
	 * pointer for the parameters
	 */
	flush_cache_all();
	outer_clean_range(__pa(param), __pa(param + 5));
	ret = omap_smc2(idx, flag, __pa(param));

	return ret;
}