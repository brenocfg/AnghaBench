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
struct it87_data {int in_scaled; } ;

/* Variables and functions */
 int BIT (int) ; 
 scalar_t__ has_10_9mv_adc (struct it87_data const*) ; 
 scalar_t__ has_12mv_adc (struct it87_data const*) ; 

__attribute__((used)) static int adc_lsb(const struct it87_data *data, int nr)
{
	int lsb;

	if (has_12mv_adc(data))
		lsb = 120;
	else if (has_10_9mv_adc(data))
		lsb = 109;
	else
		lsb = 160;
	if (data->in_scaled & BIT(nr))
		lsb <<= 1;
	return lsb;
}