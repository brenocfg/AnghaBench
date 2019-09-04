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
typedef  int /*<<< orphan*/  u16 ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int DIV_ROUND_CLOSEST (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INA226_SHIFT_AVG (int) ; 
 int /*<<< orphan*/  INA226_TOTAL_CONV_TIME_DEFAULT ; 
 int find_closest (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ina226_avg_tab ; 

__attribute__((used)) static u16 ina226_interval_to_reg(int interval)
{
	int avg, avg_bits;

	avg = DIV_ROUND_CLOSEST(interval * 1000,
				INA226_TOTAL_CONV_TIME_DEFAULT);
	avg_bits = find_closest(avg, ina226_avg_tab,
				ARRAY_SIZE(ina226_avg_tab));

	return INA226_SHIFT_AVG(avg_bits);
}