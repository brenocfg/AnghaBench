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
 int exin_avail ; 
 int* ltq_eiu_irq ; 

int ltq_eiu_get_irq(int exin)
{
	if (exin < exin_avail)
		return ltq_eiu_irq[exin];
	return -1;
}