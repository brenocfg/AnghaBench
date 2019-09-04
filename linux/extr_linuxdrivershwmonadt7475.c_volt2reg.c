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
 int** adt7473_in_scaling ; 
 int clamp_val (long,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline u16 volt2reg(int channel, long volt, u8 bypass_attn)
{
	const int *r = adt7473_in_scaling[channel];
	long reg;

	if (bypass_attn & (1 << channel))
		reg = (volt * 1024) / 2250;
	else
		reg = (volt * r[1] * 1024) / ((r[0] + r[1]) * 2250);
	return clamp_val(reg, 0, 1023) & (0xff << 2);
}