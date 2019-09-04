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
 scalar_t__ cpu_is_xlpii () ; 
 unsigned int nlm_xlp2_get_pic_frequency (int) ; 

unsigned int nlm_get_pic_frequency(int node)
{
	if (cpu_is_xlpii())
		return nlm_xlp2_get_pic_frequency(node);
	else
		return 133333333;
}