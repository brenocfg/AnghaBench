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
struct engine {int dummy; } ;
typedef  enum i2caux_engine_type { ____Placeholder_i2caux_engine_type } i2caux_engine_type ;

/* Variables and functions */
 int I2CAUX_ENGINE_TYPE_I2C_GENERIC_HW ; 

enum i2caux_engine_type dal_i2c_generic_hw_engine_get_engine_type(
	const struct engine *engine)
{
	return I2CAUX_ENGINE_TYPE_I2C_GENERIC_HW;
}