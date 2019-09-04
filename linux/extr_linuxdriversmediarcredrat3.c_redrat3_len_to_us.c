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
 int RR3_CLK_CONV_FACTOR ; 

__attribute__((used)) static u32 redrat3_len_to_us(u32 length)
{
	u32 biglen = length * 1000;
	u32 divisor = (RR3_CLK_CONV_FACTOR) / 1000;
	u32 result = (u32) (biglen / divisor);

	/* don't allow zero lengths to go back, breaks lirc */
	return result ? result : 1;
}