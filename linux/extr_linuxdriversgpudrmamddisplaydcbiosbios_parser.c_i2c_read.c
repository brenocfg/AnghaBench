#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
struct i2c_payload {int address; int length; int write; int /*<<< orphan*/ * data; } ;
struct i2c_command {int /*<<< orphan*/  number_of_payloads; struct i2c_payload* payloads; int /*<<< orphan*/  speed; int /*<<< orphan*/  engine; } ;
struct TYPE_9__ {int clk_a_shift; int /*<<< orphan*/  clk_a_register_index; } ;
struct graphics_object_i2c_info {int i2c_slave_address; TYPE_3__ gpio_info; int /*<<< orphan*/  i2c_line; int /*<<< orphan*/  i2c_hw_assist; } ;
struct gpio_ddc_hw_info {int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct ddc {TYPE_6__* ctx; } ;
struct TYPE_8__ {TYPE_1__* ctx; } ;
struct bios_parser {TYPE_2__ base; } ;
typedef  int /*<<< orphan*/  offset ;
struct TYPE_12__ {int /*<<< orphan*/  i2caux; TYPE_5__* dc; } ;
struct TYPE_10__ {int /*<<< orphan*/  i2c_speed_in_khz; } ;
struct TYPE_11__ {TYPE_4__ caps; } ;
struct TYPE_7__ {int /*<<< orphan*/  gpio_service; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (struct i2c_payload*) ; 
 int /*<<< orphan*/  I2C_COMMAND_ENGINE_SW ; 
 struct ddc* dal_gpio_create_ddc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct gpio_ddc_hw_info*) ; 
 int /*<<< orphan*/  dal_gpio_destroy_ddc (struct ddc**) ; 
 int dal_i2caux_submit_i2c_command (int /*<<< orphan*/ ,struct ddc*,struct i2c_command*) ; 

__attribute__((used)) static bool i2c_read(
	struct bios_parser *bp,
	struct graphics_object_i2c_info *i2c_info,
	uint8_t *buffer,
	uint32_t length)
{
	struct ddc *ddc;
	uint8_t offset[2] = { 0, 0 };
	bool result = false;
	struct i2c_command cmd;
	struct gpio_ddc_hw_info hw_info = {
		i2c_info->i2c_hw_assist,
		i2c_info->i2c_line };

	ddc = dal_gpio_create_ddc(bp->base.ctx->gpio_service,
		i2c_info->gpio_info.clk_a_register_index,
		(1 << i2c_info->gpio_info.clk_a_shift), &hw_info);

	if (!ddc)
		return result;

	/*Using SW engine */
	cmd.engine = I2C_COMMAND_ENGINE_SW;
	cmd.speed = ddc->ctx->dc->caps.i2c_speed_in_khz;

	{
		struct i2c_payload payloads[] = {
				{
						.address = i2c_info->i2c_slave_address >> 1,
						.data = offset,
						.length = sizeof(offset),
						.write = true
				},
				{
						.address = i2c_info->i2c_slave_address >> 1,
						.data = buffer,
						.length = length,
						.write = false
				}
		};

		cmd.payloads = payloads;
		cmd.number_of_payloads = ARRAY_SIZE(payloads);

		/* TODO route this through drm i2c_adapter */
		result = dal_i2caux_submit_i2c_command(
				ddc->ctx->i2caux,
				ddc,
				&cmd);
	}

	dal_gpio_destroy_ddc(&ddc);

	return result;
}