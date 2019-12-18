#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int clk_a_shift; int /*<<< orphan*/  clk_a_register_index; } ;
struct graphics_object_i2c_info {TYPE_3__ gpio_info; int /*<<< orphan*/  i2c_hw_assist; int /*<<< orphan*/  i2c_line; } ;
struct gpio_service {int dummy; } ;
struct gpio_ddc_hw_info {int /*<<< orphan*/  hw_supported; int /*<<< orphan*/  ddc_channel; } ;
struct ddc_service_init_data {int /*<<< orphan*/  id; TYPE_1__* ctx; int /*<<< orphan*/  link; } ;
struct TYPE_10__ {scalar_t__ raw; } ;
struct TYPE_9__ {int EDID_QUERY_DONE_ONCE; int FORCE_READ_REPEATED_START; int EDID_STRESS_READ; int IS_INTERNAL_DISPLAY; } ;
struct ddc_service {TYPE_5__ wa; TYPE_4__ flags; int /*<<< orphan*/ * ddc_pin; TYPE_1__* ctx; int /*<<< orphan*/  link; } ;
struct dc_bios {TYPE_2__* funcs; } ;
typedef  enum connector_id { ____Placeholder_connector_id } connector_id ;
struct TYPE_7__ {scalar_t__ (* get_i2c_info ) (struct dc_bios*,int /*<<< orphan*/ ,struct graphics_object_i2c_info*) ;} ;
struct TYPE_6__ {struct dc_bios* dc_bios; struct gpio_service* gpio_service; } ;

/* Variables and functions */
 scalar_t__ BP_RESULT_OK ; 
 int CONNECTOR_ID_EDP ; 
 int CONNECTOR_ID_LVDS ; 
 int /*<<< orphan*/ * dal_gpio_create_ddc (struct gpio_service*,int /*<<< orphan*/ ,int,struct gpio_ddc_hw_info*) ; 
 int dal_graphics_object_id_get_connector_id (int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (struct dc_bios*,int /*<<< orphan*/ ,struct graphics_object_i2c_info*) ; 

__attribute__((used)) static void construct(
	struct ddc_service *ddc_service,
	struct ddc_service_init_data *init_data)
{
	enum connector_id connector_id =
		dal_graphics_object_id_get_connector_id(init_data->id);

	struct gpio_service *gpio_service = init_data->ctx->gpio_service;
	struct graphics_object_i2c_info i2c_info;
	struct gpio_ddc_hw_info hw_info;
	struct dc_bios *dcb = init_data->ctx->dc_bios;

	ddc_service->link = init_data->link;
	ddc_service->ctx = init_data->ctx;

	if (BP_RESULT_OK != dcb->funcs->get_i2c_info(dcb, init_data->id, &i2c_info)) {
		ddc_service->ddc_pin = NULL;
	} else {
		hw_info.ddc_channel = i2c_info.i2c_line;
		hw_info.hw_supported = i2c_info.i2c_hw_assist;

		ddc_service->ddc_pin = dal_gpio_create_ddc(
			gpio_service,
			i2c_info.gpio_info.clk_a_register_index,
			1 << i2c_info.gpio_info.clk_a_shift,
			&hw_info);
	}

	ddc_service->flags.EDID_QUERY_DONE_ONCE = false;
	ddc_service->flags.FORCE_READ_REPEATED_START = false;
	ddc_service->flags.EDID_STRESS_READ = false;

	ddc_service->flags.IS_INTERNAL_DISPLAY =
		connector_id == CONNECTOR_ID_EDP ||
		connector_id == CONNECTOR_ID_LVDS;

	ddc_service->wa.raw = 0;
}