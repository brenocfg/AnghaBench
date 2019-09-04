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
 int RPI_FIRMWARE_GET_CLOCK_RATE ; 
 int RPI_FIRMWARE_GET_MAX_CLOCK_RATE ; 
 int RPI_FIRMWARE_GET_MIN_CLOCK_RATE ; 
 int /*<<< orphan*/  VCMSG_ID_ARM_CLOCK ; 
 int bcm2835_cpufreq_clock_property (int,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  print_debug (char*,char*,int) ; 
 int /*<<< orphan*/  print_err (char*,int) ; 

__attribute__((used)) static uint32_t bcm2835_cpufreq_get_clock(int tag)
{
	u32 rate;
	int ret;

	ret = bcm2835_cpufreq_clock_property(tag, VCMSG_ID_ARM_CLOCK, &rate);
	if (ret) {
		print_err("Failed to get clock (%d)\n", ret);
		return 0;
	}

	rate /= 1000;
	print_debug("%s frequency = %u\n",
		tag == RPI_FIRMWARE_GET_CLOCK_RATE ? "Current":
		tag == RPI_FIRMWARE_GET_MIN_CLOCK_RATE ? "Min":
		tag == RPI_FIRMWARE_GET_MAX_CLOCK_RATE ? "Max":
		"Unexpected", rate);

	return rate;
}