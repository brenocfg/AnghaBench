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
 int IR_MAX_DURATION ; 
 int RR3_CLK_CONV_FACTOR ; 

__attribute__((used)) static u32 redrat3_us_to_len(u32 microsec)
{
	u32 result;
	u32 divisor;

	microsec = (microsec > IR_MAX_DURATION) ? IR_MAX_DURATION : microsec;
	divisor = (RR3_CLK_CONV_FACTOR / 1000);
	result = (u32)(microsec * divisor) / 1000;

	/* don't allow zero lengths to go back, breaks lirc */
	return result ? result : 1;
}