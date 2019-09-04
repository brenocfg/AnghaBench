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
struct i2c_engine {int dummy; } ;
struct ddc {int dummy; } ;

/* Variables and functions */
 int dal_i2caux_i2c_sw_engine_acquire_engine (struct i2c_engine*,struct ddc*) ; 

__attribute__((used)) static bool acquire_engine(
	struct i2c_engine *engine,
	struct ddc *ddc_handle)
{
	return dal_i2caux_i2c_sw_engine_acquire_engine(engine, ddc_handle);
}