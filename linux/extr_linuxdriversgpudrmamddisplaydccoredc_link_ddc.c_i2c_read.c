#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
struct i2c_payload {int write; int address; int length; int /*<<< orphan*/ * data; } ;
struct i2c_command {int number_of_payloads; int /*<<< orphan*/  speed; int /*<<< orphan*/  engine; struct i2c_payload* payloads; } ;
struct ddc_service {int /*<<< orphan*/  link; TYPE_3__* ctx; } ;
struct TYPE_6__ {TYPE_2__* dc; } ;
struct TYPE_4__ {int /*<<< orphan*/  i2c_speed_in_khz; } ;
struct TYPE_5__ {TYPE_1__ caps; } ;

/* Variables and functions */
 int /*<<< orphan*/  DDC_I2C_COMMAND_ENGINE ; 
 int dm_helpers_submit_i2c (TYPE_3__*,int /*<<< orphan*/ ,struct i2c_command*) ; 

__attribute__((used)) static bool i2c_read(
	struct ddc_service *ddc,
	uint32_t address,
	uint8_t *buffer,
	uint32_t len)
{
	uint8_t offs_data = 0;
	struct i2c_payload payloads[2] = {
		{
		.write = true,
		.address = address,
		.length = 1,
		.data = &offs_data },
		{
		.write = false,
		.address = address,
		.length = len,
		.data = buffer } };

	struct i2c_command command = {
		.payloads = payloads,
		.number_of_payloads = 2,
		.engine = DDC_I2C_COMMAND_ENGINE,
		.speed = ddc->ctx->dc->caps.i2c_speed_in_khz };

	return dm_helpers_submit_i2c(
			ddc->ctx,
			ddc->link,
			&command);
}