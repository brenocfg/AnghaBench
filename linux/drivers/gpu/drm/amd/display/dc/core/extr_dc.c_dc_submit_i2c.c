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
typedef  size_t uint32_t ;
struct i2c_command {int dummy; } ;
struct ddc_service {int /*<<< orphan*/  ddc_pin; } ;
struct dc_link {struct ddc_service* ddc; } ;
struct dc {int /*<<< orphan*/  res_pool; struct dc_link** links; } ;

/* Variables and functions */
 int dce_i2c_submit_command (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct i2c_command*) ; 

bool dc_submit_i2c(
		struct dc *dc,
		uint32_t link_index,
		struct i2c_command *cmd)
{

	struct dc_link *link = dc->links[link_index];
	struct ddc_service *ddc = link->ddc;
	return dce_i2c_submit_command(
		dc->res_pool,
		ddc->ddc_pin,
		cmd);
}