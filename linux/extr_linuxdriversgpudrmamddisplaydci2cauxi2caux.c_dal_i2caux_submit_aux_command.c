#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_6__ {int address; int /*<<< orphan*/  data; int /*<<< orphan*/  length; int /*<<< orphan*/  address_space; } ;
struct i2caux_transaction_request {TYPE_1__ payload; int /*<<< orphan*/  operation; int /*<<< orphan*/  member_0; } ;
struct i2caux {TYPE_3__* funcs; } ;
struct ddc {int dummy; } ;
struct aux_payload {int address; int /*<<< orphan*/  data; int /*<<< orphan*/  length; scalar_t__ write; scalar_t__ i2c_over_aux; } ;
struct TYPE_9__ {TYPE_2__* funcs; } ;
struct aux_engine {TYPE_4__ base; int /*<<< orphan*/  max_defer_write_retry; int /*<<< orphan*/  delay; } ;
struct aux_command {int number_of_payloads; scalar_t__ mot; struct aux_payload* payloads; int /*<<< orphan*/  max_defer_write_retry; int /*<<< orphan*/  defer_delay; } ;
struct TYPE_8__ {int /*<<< orphan*/  (* release_engine ) (struct i2caux*,TYPE_4__*) ;struct aux_engine* (* acquire_aux_engine ) (struct i2caux*,struct ddc*) ;} ;
struct TYPE_7__ {int /*<<< orphan*/  (* submit_request ) (TYPE_4__*,struct i2caux_transaction_request*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BREAK_TO_DEBUGGER () ; 
 int /*<<< orphan*/  I2CAUX_TRANSACTION_ADDRESS_SPACE_DPCD ; 
 int /*<<< orphan*/  I2CAUX_TRANSACTION_ADDRESS_SPACE_I2C ; 
 int /*<<< orphan*/  I2CAUX_TRANSACTION_READ ; 
 int /*<<< orphan*/  I2CAUX_TRANSACTION_WRITE ; 
 scalar_t__ I2C_MOT_TRUE ; 
 scalar_t__ I2C_MOT_UNDEF ; 
 struct aux_engine* stub1 (struct i2caux*,struct ddc*) ; 
 int /*<<< orphan*/  stub2 (TYPE_4__*,struct i2caux_transaction_request*,int) ; 
 int /*<<< orphan*/  stub3 (struct i2caux*,TYPE_4__*) ; 

bool dal_i2caux_submit_aux_command(
	struct i2caux *i2caux,
	struct ddc *ddc,
	struct aux_command *cmd)
{
	struct aux_engine *engine;
	uint8_t index_of_payload = 0;
	bool result;
	bool mot;

	if (!ddc) {
		BREAK_TO_DEBUGGER();
		return false;
	}

	if (!cmd) {
		BREAK_TO_DEBUGGER();
		return false;
	}

	engine = i2caux->funcs->acquire_aux_engine(i2caux, ddc);

	if (!engine)
		return false;

	engine->delay = cmd->defer_delay;
	engine->max_defer_write_retry = cmd->max_defer_write_retry;

	result = true;

	while (index_of_payload < cmd->number_of_payloads) {
		struct aux_payload *payload = cmd->payloads + index_of_payload;
		struct i2caux_transaction_request request = { 0 };

		if (cmd->mot == I2C_MOT_UNDEF)
			mot = (index_of_payload != cmd->number_of_payloads - 1);
		else
			mot = (cmd->mot == I2C_MOT_TRUE);

		request.operation = payload->write ?
			I2CAUX_TRANSACTION_WRITE :
			I2CAUX_TRANSACTION_READ;

		if (payload->i2c_over_aux) {
			request.payload.address_space =
				I2CAUX_TRANSACTION_ADDRESS_SPACE_I2C;

			request.payload.address = (payload->address << 1) |
				!payload->write;
		} else {
			request.payload.address_space =
				I2CAUX_TRANSACTION_ADDRESS_SPACE_DPCD;

			request.payload.address = payload->address;
		}

		request.payload.length = payload->length;
		request.payload.data = payload->data;

		if (!engine->base.funcs->submit_request(
			&engine->base, &request, mot)) {
			result = false;
			break;
		}

		++index_of_payload;
	}

	i2caux->funcs->release_engine(i2caux, &engine->base);

	return result;
}