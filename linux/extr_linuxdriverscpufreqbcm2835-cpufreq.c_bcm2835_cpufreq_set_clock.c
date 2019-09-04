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
typedef  int uint32_t ;
typedef  int u32 ;

/* Variables and functions */
 int /*<<< orphan*/  RPI_FIRMWARE_SET_CLOCK_RATE ; 
 int /*<<< orphan*/  VCMSG_ID_ARM_CLOCK ; 
 int bcm2835_cpufreq_clock_property (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  print_debug (char*,int,int,int) ; 
 int /*<<< orphan*/  print_err (char*,int,int) ; 

__attribute__((used)) static uint32_t bcm2835_cpufreq_set_clock(int cur_rate, int arm_rate)
{
	u32 rate = arm_rate * 1000;
	int ret;

	ret = bcm2835_cpufreq_clock_property(RPI_FIRMWARE_SET_CLOCK_RATE, VCMSG_ID_ARM_CLOCK, &rate);
	if (ret) {
		print_err("Failed to set clock: %d (%d)\n", arm_rate, ret);
		return 0;
	}

	rate /= 1000;
	print_debug("Setting new frequency = %d -> %d (actual %d)\n", cur_rate, arm_rate, rate);

	return rate;
}