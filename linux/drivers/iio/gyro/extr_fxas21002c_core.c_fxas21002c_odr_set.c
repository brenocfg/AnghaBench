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
 int /*<<< orphan*/  F_DR ; 
 int fxas21002c_odr_value_from_hz (struct fxas21002c_data*,int) ; 
 int fxas21002c_write (struct fxas21002c_data*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int fxas21002c_odr_set(struct fxas21002c_data *data, int odr)
{
	int odr_bits;

	odr_bits = fxas21002c_odr_value_from_hz(data, odr);
	if (odr_bits < 0)
		return odr_bits;

	return fxas21002c_write(data, F_DR, odr_bits);
}