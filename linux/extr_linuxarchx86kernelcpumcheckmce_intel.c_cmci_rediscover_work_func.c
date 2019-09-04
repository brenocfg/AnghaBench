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
 int /*<<< orphan*/  cmci_discover (int) ; 
 scalar_t__ cmci_supported (int*) ; 

__attribute__((used)) static void cmci_rediscover_work_func(void *arg)
{
	int banks;

	/* Recheck banks in case CPUs don't all have the same */
	if (cmci_supported(&banks))
		cmci_discover(banks);
}