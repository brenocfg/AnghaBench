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
 scalar_t__ mce_evt_pool ; 
 int mce_gen_pool_create () ; 

int mce_gen_pool_init(void)
{
	/* Just init mce_gen_pool once. */
	if (mce_evt_pool)
		return 0;

	return mce_gen_pool_create();
}