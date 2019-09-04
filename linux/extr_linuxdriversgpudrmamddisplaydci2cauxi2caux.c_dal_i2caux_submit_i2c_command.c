#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_8__ {int address; int /*<<< orphan*/  data; int /*<<< orphan*/  length; int /*<<< orphan*/  address_space; } ;
struct i2caux_transaction_request {TYPE_2__ payload; int /*<<< orphan*/  operation; int /*<<< orphan*/  member_0; } ;
struct i2caux {TYPE_4__* funcs; } ;
struct i2c_payload {int address; int /*<<< orphan*/  data; int /*<<< orphan*/  length; scalar_t__ write; } ;
struct TYPE_11__ {TYPE_3__* funcs; } ;
struct i2c_engine {TYPE_5__ base; TYPE_1__* funcs; } ;
struct i2c_command {int engine; int number_of_payloads; struct i2c_payload* payloads; int /*<<< orphan*/  speed; } ;
struct ddc {int dummy; } ;
struct TYPE_10__ {int /*<<< orphan*/  (* release_engine ) (struct i2caux*,TYPE_5__*) ;struct i2c_engine* (* acquire_i2c_sw_engine ) (struct i2caux*,struct ddc*) ;struct i2c_engine* (* acquire_i2c_hw_engine ) (struct i2caux*,struct ddc*) ;} ;
struct TYPE_9__ {int /*<<< orphan*/  (* submit_request ) (TYPE_5__*,struct i2caux_transaction_request*,int) ;} ;
struct TYPE_7__ {int /*<<< orphan*/  (* set_speed ) (struct i2c_engine*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BREAK_TO_DEBUGGER () ; 
 int /*<<< orphan*/  I2CAUX_TRANSACTION_ADDRESS_SPACE_I2C ; 
 int /*<<< orphan*/  I2CAUX_TRANSACTION_READ ; 
 int /*<<< orphan*/  I2CAUX_TRANSACTION_WRITE ; 
#define  I2C_COMMAND_ENGINE_DEFAULT 130 
#define  I2C_COMMAND_ENGINE_HW 129 
#define  I2C_COMMAND_ENGINE_SW 128 
 struct i2c_engine* stub1 (struct i2caux*,struct ddc*) ; 
 struct i2c_engine* stub2 (struct i2caux*,struct ddc*) ; 
 struct i2c_engine* stub3 (struct i2caux*,struct ddc*) ; 
 struct i2c_engine* stub4 (struct i2caux*,struct ddc*) ; 
 int /*<<< orphan*/  stub5 (struct i2c_engine*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub6 (TYPE_5__*,struct i2caux_transaction_request*,int) ; 
 int /*<<< orphan*/  stub7 (struct i2caux*,TYPE_5__*) ; 

bool dal_i2caux_submit_i2c_command(
	struct i2caux *i2caux,
	struct ddc *ddc,
	struct i2c_command *cmd)
{
	struct i2c_engine *engine;
	uint8_t index_of_payload = 0;
	bool result;

	if (!ddc) {
		BREAK_TO_DEBUGGER();
		return false;
	}

	if (!cmd) {
		BREAK_TO_DEBUGGER();
		return false;
	}

	/*
	 * default will be SW, however there is a feature flag in adapter
	 * service that determines whether SW i2c_engine will be available or
	 * not, if sw i2c is not available we will fallback to hw. This feature
	 * flag is set to not creating sw i2c engine for every dce except dce80
	 * currently
	 */
	switch (cmd->engine) {
	case I2C_COMMAND_ENGINE_DEFAULT:
	case I2C_COMMAND_ENGINE_SW:
		/* try to acquire SW engine first,
		 * acquire HW engine if SW engine not available */
		engine = i2caux->funcs->acquire_i2c_sw_engine(i2caux, ddc);

		if (!engine)
			engine = i2caux->funcs->acquire_i2c_hw_engine(
				i2caux, ddc);
	break;
	case I2C_COMMAND_ENGINE_HW:
	default:
		/* try to acquire HW engine first,
		 * acquire SW engine if HW engine not available */
		engine = i2caux->funcs->acquire_i2c_hw_engine(i2caux, ddc);

		if (!engine)
			engine = i2caux->funcs->acquire_i2c_sw_engine(
				i2caux, ddc);
	}

	if (!engine)
		return false;

	engine->funcs->set_speed(engine, cmd->speed);

	result = true;

	while (index_of_payload < cmd->number_of_payloads) {
		bool mot = (index_of_payload != cmd->number_of_payloads - 1);

		struct i2c_payload *payload = cmd->payloads + index_of_payload;

		struct i2caux_transaction_request request = { 0 };

		request.operation = payload->write ?
			I2CAUX_TRANSACTION_WRITE :
			I2CAUX_TRANSACTION_READ;

		request.payload.address_space =
			I2CAUX_TRANSACTION_ADDRESS_SPACE_I2C;
		request.payload.address = (payload->address << 1) |
			!payload->write;
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