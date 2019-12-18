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
 int ARRAY_SIZE (scalar_t__*) ; 
 scalar_t__* vmmouse_supported_hypervisors ; 
 scalar_t__ x86_hyper_type ; 

__attribute__((used)) static bool vmmouse_check_hypervisor(void)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(vmmouse_supported_hypervisors); i++)
		if (vmmouse_supported_hypervisors[i] == x86_hyper_type)
			return true;

	return false;
}