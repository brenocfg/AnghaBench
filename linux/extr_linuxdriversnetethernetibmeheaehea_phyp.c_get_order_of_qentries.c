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
typedef  unsigned int u8 ;
typedef  unsigned int u16 ;

/* Variables and functions */

__attribute__((used)) static inline u16 get_order_of_qentries(u16 queue_entries)
{
	u8 ld = 1;		/*  logarithmus dualis */
	while (((1U << ld) - 1) < queue_entries)
		ld++;
	return ld - 1;
}