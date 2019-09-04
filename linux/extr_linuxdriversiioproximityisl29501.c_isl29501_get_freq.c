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
struct isl29501_private {int dummy; } ;

/* Variables and functions */
 int IIO_VAL_INT_PLUS_MICRO ; 
 int /*<<< orphan*/  REG_SAMPLE_TIME ; 
 int do_div (unsigned long long,int) ; 
 int isl29501_register_read (struct isl29501_private*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int isl29501_get_freq(struct isl29501_private *isl29501,
			     int *val, int *val2)
{
	int ret;
	int sample_time;
	unsigned long long freq;
	u32 temp;

	ret = isl29501_register_read(isl29501, REG_SAMPLE_TIME, &sample_time);
	if (ret < 0)
		return ret;

	/* freq = 1 / (0.000450 * (sample_time + 1) * 10^-6) */
	freq = 1000000ULL * 1000000ULL;

	do_div(freq, 450 * (sample_time + 1));

	temp = do_div(freq, 1000000);
	*val = freq;
	*val2 = temp;

	return IIO_VAL_INT_PLUS_MICRO;
}