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
struct resource_pool {int dummy; } ;
struct dce_i2c_sw {int /*<<< orphan*/ * ddc; } ;

/* Variables and functions */
 int /*<<< orphan*/  dal_ddc_close (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void release_engine_dce_sw(
	struct resource_pool *pool,
	struct dce_i2c_sw *dce_i2c_sw)
{
	dal_ddc_close(dce_i2c_sw->ddc);
	dce_i2c_sw->ddc = NULL;
}