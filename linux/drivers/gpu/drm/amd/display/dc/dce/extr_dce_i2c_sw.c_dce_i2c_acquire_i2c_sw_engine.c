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
struct resource_pool {struct dce_i2c_sw** sw_i2cs; } ;
struct ddc {int dummy; } ;
struct dce_i2c_sw {int dummy; } ;
typedef  enum gpio_ddc_line { ____Placeholder_gpio_ddc_line } gpio_ddc_line ;

/* Variables and functions */
 int /*<<< orphan*/  dce_i2c_engine_acquire_sw (struct dce_i2c_sw*,struct ddc*) ; 
 scalar_t__ get_hw_supported_ddc_line (struct ddc*,int*) ; 

struct dce_i2c_sw *dce_i2c_acquire_i2c_sw_engine(
	struct resource_pool *pool,
	struct ddc *ddc)
{
	enum gpio_ddc_line line;
	struct dce_i2c_sw *engine = NULL;

	if (get_hw_supported_ddc_line(ddc, &line))
		engine = pool->sw_i2cs[line];

	if (!engine)
		return NULL;

	if (!dce_i2c_engine_acquire_sw(engine, ddc))
		return NULL;

	return engine;
}