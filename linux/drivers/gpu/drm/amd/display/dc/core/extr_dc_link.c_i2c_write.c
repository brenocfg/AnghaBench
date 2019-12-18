#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct pipe_ctx {TYPE_3__* stream; } ;
struct i2c_payload {int number_of_payloads; int write; struct i2c_payload* payloads; int /*<<< orphan*/  length; int /*<<< orphan*/ * data; int /*<<< orphan*/  address; int /*<<< orphan*/  speed; int /*<<< orphan*/  engine; int /*<<< orphan*/  member_0; } ;
struct i2c_command {int number_of_payloads; int write; struct i2c_command* payloads; int /*<<< orphan*/  length; int /*<<< orphan*/ * data; int /*<<< orphan*/  address; int /*<<< orphan*/  speed; int /*<<< orphan*/  engine; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  payload ;
typedef  int /*<<< orphan*/  cmd ;
struct TYPE_8__ {TYPE_2__* dc; } ;
struct TYPE_7__ {int /*<<< orphan*/  link; TYPE_4__* ctx; } ;
struct TYPE_5__ {int /*<<< orphan*/  i2c_speed_in_khz; } ;
struct TYPE_6__ {TYPE_1__ caps; } ;

/* Variables and functions */
 int /*<<< orphan*/  I2C_COMMAND_ENGINE_DEFAULT ; 
 scalar_t__ dm_helpers_submit_i2c (TYPE_4__*,int /*<<< orphan*/ ,struct i2c_payload*) ; 
 int /*<<< orphan*/  memset (struct i2c_payload*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static bool i2c_write(struct pipe_ctx *pipe_ctx,
		uint8_t address, uint8_t *buffer, uint32_t length)
{
	struct i2c_command cmd = {0};
	struct i2c_payload payload = {0};

	memset(&payload, 0, sizeof(payload));
	memset(&cmd, 0, sizeof(cmd));

	cmd.number_of_payloads = 1;
	cmd.engine = I2C_COMMAND_ENGINE_DEFAULT;
	cmd.speed = pipe_ctx->stream->ctx->dc->caps.i2c_speed_in_khz;

	payload.address = address;
	payload.data = buffer;
	payload.length = length;
	payload.write = true;
	cmd.payloads = &payload;

	if (dm_helpers_submit_i2c(pipe_ctx->stream->ctx,
			pipe_ctx->stream->link, &cmd))
		return true;

	return false;
}