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

/* Variables and functions */
 int CLK_DIV_1 ; 
 int SSC_DEPTH_4M ; 

__attribute__((used)) static u8 revise_ssc_depth(u8 ssc_depth, u8 div)
{
	if (div > CLK_DIV_1) {
		if (ssc_depth > (div - 1))
			ssc_depth -= (div - 1);
		else
			ssc_depth = SSC_DEPTH_4M;
	}

	return ssc_depth;
}