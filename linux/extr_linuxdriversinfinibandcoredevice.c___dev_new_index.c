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
typedef  int u32 ;

/* Variables and functions */
 int /*<<< orphan*/  __ib_device_get_by_index (int) ; 

__attribute__((used)) static u32 __dev_new_index(void)
{
	/*
	 * The device index to allow stable naming.
	 * Similar to struct net -> ifindex.
	 */
	static u32 index;

	for (;;) {
		if (!(++index))
			index = 1;

		if (!__ib_device_get_by_index(index))
			return index;
	}
}