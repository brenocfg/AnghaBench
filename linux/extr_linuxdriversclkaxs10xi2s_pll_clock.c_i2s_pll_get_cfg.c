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
struct i2s_pll_cfg {int dummy; } ;

/* Variables and functions */
 struct i2s_pll_cfg const* i2s_pll_cfg_27m ; 
 struct i2s_pll_cfg const* i2s_pll_cfg_28m ; 

__attribute__((used)) static const struct i2s_pll_cfg *i2s_pll_get_cfg(unsigned long prate)
{
	switch (prate) {
	case 27000000:
		return i2s_pll_cfg_27m;
	case 28224000:
		return i2s_pll_cfg_28m;
	default:
		return NULL;
	}
}