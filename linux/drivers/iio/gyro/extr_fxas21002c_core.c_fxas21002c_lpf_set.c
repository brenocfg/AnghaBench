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
struct fxas21002c_data {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  F_BW ; 
 int fxas21002c_lpf_value_from_bw (struct fxas21002c_data*,int) ; 
 int fxas21002c_odr_get (struct fxas21002c_data*,int*) ; 
 int fxas21002c_write (struct fxas21002c_data*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int fxas21002c_lpf_set(struct fxas21002c_data *data, int bw)
{
	int bw_bits;
	int odr;
	int ret;

	bw_bits = fxas21002c_lpf_value_from_bw(data, bw);
	if (bw_bits < 0)
		return bw_bits;

	/*
	 * From table 33 of the device spec, for ODR = 25Hz and 12.5 value 0.08
	 * is not allowed and for ODR = 12.5 value 0.16 is also not allowed
	 */
	ret = fxas21002c_odr_get(data, &odr);
	if (ret < 0)
		return -EINVAL;

	if ((odr == 25 && bw_bits > 0x01) || (odr == 12 && bw_bits > 0))
		return -EINVAL;

	return fxas21002c_write(data, F_BW, bw_bits);
}