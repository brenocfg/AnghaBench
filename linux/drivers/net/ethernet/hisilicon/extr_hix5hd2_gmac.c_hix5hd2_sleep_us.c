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
 int DIV_ROUND_UP (int,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static void hix5hd2_sleep_us(u32 time_us)
{
	u32 time_ms;

	if (!time_us)
		return;

	time_ms = DIV_ROUND_UP(time_us, 1000);
	if (time_ms < 20)
		usleep_range(time_us, time_us + 500);
	else
		msleep(time_ms);
}