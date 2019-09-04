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
 int /*<<< orphan*/  detect_memory_88 () ; 
 int /*<<< orphan*/  detect_memory_e801 () ; 
 scalar_t__ detect_memory_e820 () ; 

int detect_memory(void)
{
	int err = -1;

	if (detect_memory_e820() > 0)
		err = 0;

	if (!detect_memory_e801())
		err = 0;

	if (!detect_memory_88())
		err = 0;

	return err;
}