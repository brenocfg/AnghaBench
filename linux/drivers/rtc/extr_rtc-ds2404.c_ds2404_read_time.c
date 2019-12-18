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
typedef  int /*<<< orphan*/  u8 ;
struct rtc_time {int dummy; } ;
struct device {int dummy; } ;
typedef  scalar_t__ __le32 ;

/* Variables and functions */
 int /*<<< orphan*/  ds2404_read_memory (struct device*,int,int,int /*<<< orphan*/ *) ; 
 unsigned long le32_to_cpu (scalar_t__) ; 
 int /*<<< orphan*/  rtc_time64_to_tm (unsigned long,struct rtc_time*) ; 

__attribute__((used)) static int ds2404_read_time(struct device *dev, struct rtc_time *dt)
{
	unsigned long time = 0;
	__le32 hw_time = 0;

	ds2404_read_memory(dev, 0x203, 4, (u8 *)&hw_time);
	time = le32_to_cpu(hw_time);

	rtc_time64_to_tm(time, dt);
	return 0;
}