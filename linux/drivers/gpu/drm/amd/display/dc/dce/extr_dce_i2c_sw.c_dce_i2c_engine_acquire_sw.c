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
struct ddc {int dummy; } ;
struct dce_i2c_sw {int dummy; } ;

/* Variables and functions */
 int dce_i2c_sw_engine_acquire_engine (struct dce_i2c_sw*,struct ddc*) ; 
 int /*<<< orphan*/  udelay (int) ; 

bool dce_i2c_engine_acquire_sw(
	struct dce_i2c_sw *dce_i2c_sw,
	struct ddc *ddc_handle)
{
	uint32_t counter = 0;
	bool result;

	do {

		result = dce_i2c_sw_engine_acquire_engine(
				dce_i2c_sw, ddc_handle);

		if (result)
			break;

		/* i2c_engine is busy by VBios, lets wait and retry */

		udelay(10);

		++counter;
	} while (counter < 2);

	return result;
}