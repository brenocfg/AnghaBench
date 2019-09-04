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
typedef  int u16 ;
struct adt7475_data {int config5; } ;

/* Variables and functions */
 int CONFIG5_TWOSCOMP ; 
 long clamp_val (long,int,int) ; 

__attribute__((used)) static inline u16 temp2reg(struct adt7475_data *data, long val)
{
	u16 ret;

	if (!(data->config5 & CONFIG5_TWOSCOMP)) {
		val = clamp_val(val, -64000, 191000);
		ret = (val + 64500) / 1000;
	} else {
		val = clamp_val(val, -128000, 127000);
		if (val < -500)
			ret = (256500 + val) / 1000;
		else
			ret = (val + 500) / 1000;
	}

	return ret << 2;
}