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
struct isl29501_private {int dummy; } ;

/* Variables and functions */
 int ERANGE ; 
 int /*<<< orphan*/  REG_SAMPLE_TIME ; 
 int /*<<< orphan*/  do_div (unsigned long long,int) ; 
 int isl29501_register_write (struct isl29501_private*,int /*<<< orphan*/ ,unsigned long long) ; 

__attribute__((used)) static int isl29501_set_freq(struct isl29501_private *isl29501,
			     int val, int val2)
{
	int freq;
	unsigned long long sample_time;

	/* sample_freq = 1 / (0.000450 * (sample_time + 1) * 10^-6) */
	freq = val * 1000000 + val2 % 1000000;
	sample_time = 2222ULL * 1000000ULL;
	do_div(sample_time, freq);

	sample_time -= 1;

	if (sample_time > 255)
		return -ERANGE;

	return isl29501_register_write(isl29501, REG_SAMPLE_TIME, sample_time);
}