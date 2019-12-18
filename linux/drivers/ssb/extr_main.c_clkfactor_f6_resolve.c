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
typedef  int u32 ;

/* Variables and functions */
#define  SSB_CHIPCO_CLK_F6_2 133 
#define  SSB_CHIPCO_CLK_F6_3 132 
#define  SSB_CHIPCO_CLK_F6_4 131 
#define  SSB_CHIPCO_CLK_F6_5 130 
#define  SSB_CHIPCO_CLK_F6_6 129 
#define  SSB_CHIPCO_CLK_F6_7 128 

__attribute__((used)) static u32 clkfactor_f6_resolve(u32 v)
{
	/* map the magic values */
	switch (v) {
	case SSB_CHIPCO_CLK_F6_2:
		return 2;
	case SSB_CHIPCO_CLK_F6_3:
		return 3;
	case SSB_CHIPCO_CLK_F6_4:
		return 4;
	case SSB_CHIPCO_CLK_F6_5:
		return 5;
	case SSB_CHIPCO_CLK_F6_6:
		return 6;
	case SSB_CHIPCO_CLK_F6_7:
		return 7;
	}
	return 0;
}