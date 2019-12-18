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
typedef  int time64_t ;
struct timespec64 {long tv_nsec; int tv_sec; } ;
typedef  int int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  HP_SDC_CMD_LOAD_RT ; 
 int hp_sdc_rtc_read_i8042timer (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline int hp_sdc_rtc_read_rt(struct timespec64 *res) {
	int64_t raw;
	uint32_t tenms; 
	unsigned int days;

	raw = hp_sdc_rtc_read_i8042timer(HP_SDC_CMD_LOAD_RT, 5);
	if (raw < 0) return -1;

	tenms = (uint32_t)raw & 0xffffff;
	days  = (unsigned int)(raw >> 24) & 0xffff;

	res->tv_nsec = (long)(tenms % 100) * 10000 * 1000;
	res->tv_sec =  (tenms / 100) + (time64_t)days * 86400;

	return 0;
}