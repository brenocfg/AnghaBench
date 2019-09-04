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
 int PWR_MODE_MASK ; 
 int clamp_val (int,int,int) ; 

u8 cyapa_sleep_time_to_pwr_cmd(u16 sleep_time)
{
	u16 encoded_time;

	sleep_time = clamp_val(sleep_time, 20, 1000);
	encoded_time = sleep_time < 100 ? sleep_time / 10 : sleep_time / 20 + 5;
	return (encoded_time << 2) & PWR_MODE_MASK;
}