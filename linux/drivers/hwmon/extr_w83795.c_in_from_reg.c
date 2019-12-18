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
typedef  int u8 ;
typedef  int u16 ;

/* Variables and functions */

__attribute__((used)) static inline u16 in_from_reg(u8 index, u16 val)
{
	/* 3VDD, 3VSB and VBAT: 6 mV/bit; other inputs: 2 mV/bit */
	if (index >= 12 && index <= 14)
		return val * 6;
	else
		return val * 2;
}