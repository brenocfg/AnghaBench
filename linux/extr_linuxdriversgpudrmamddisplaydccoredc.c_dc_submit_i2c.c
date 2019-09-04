#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32_t ;
struct i2c_command {int dummy; } ;
struct ddc_service {int /*<<< orphan*/  ddc_pin; TYPE_1__* ctx; } ;
struct dc_link {struct ddc_service* ddc; } ;
struct dc {struct dc_link** links; } ;
struct TYPE_2__ {int /*<<< orphan*/  i2caux; } ;

/* Variables and functions */
 int dal_i2caux_submit_i2c_command (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct i2c_command*) ; 

bool dc_submit_i2c(
		struct dc *dc,
		uint32_t link_index,
		struct i2c_command *cmd)
{

	struct dc_link *link = dc->links[link_index];
	struct ddc_service *ddc = link->ddc;

	return dal_i2caux_submit_i2c_command(
		ddc->ctx->i2caux,
		ddc->ddc_pin,
		cmd);
}