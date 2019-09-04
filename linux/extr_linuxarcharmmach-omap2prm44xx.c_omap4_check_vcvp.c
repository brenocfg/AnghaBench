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
 int PRM_HAS_VOLTAGE ; 
 int prm_features ; 

__attribute__((used)) static int omap4_check_vcvp(void)
{
	if (prm_features & PRM_HAS_VOLTAGE)
		return 1;

	return 0;
}