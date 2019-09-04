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
struct irq_data {int irq; } ;

/* Variables and functions */
 scalar_t__ ATARI_ETHERNAT_PHYS_ADDR ; 
 int* enat_cpld ; 
 scalar_t__ ioremap (scalar_t__,int) ; 

__attribute__((used)) static void atari_ethernat_enable(struct irq_data *data)
{
	int enat_num = 140 - data->irq + 1;
	/*
	* map CPLD interrupt register
	*/
	if (!enat_cpld)
		enat_cpld = (unsigned char *)ioremap((ATARI_ETHERNAT_PHYS_ADDR+0x23), 0x2);
	*enat_cpld |= 1 << enat_num;
}