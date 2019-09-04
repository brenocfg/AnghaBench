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
struct TYPE_4__ {int length; int /*<<< orphan*/ * data; int /*<<< orphan*/  address; } ;
struct i2caux_transaction_request {scalar_t__ operation; int /*<<< orphan*/  status; TYPE_1__ payload; } ;
struct i2c_hw_engine {TYPE_2__* funcs; } ;
struct i2c_generic_transaction_attributes {int start_bit; int stop_bit; int last_read; int transaction_size; int /*<<< orphan*/  action; } ;
struct i2c_generic_hw_engine {TYPE_3__* funcs; struct i2c_hw_engine base; } ;
struct engine {int dummy; } ;
typedef  enum i2c_channel_operation_result { ____Placeholder_i2c_channel_operation_result } i2c_channel_operation_result ;
struct TYPE_6__ {int /*<<< orphan*/  (* read_data ) (struct i2c_generic_hw_engine*,int /*<<< orphan*/ *,int,int) ;int /*<<< orphan*/  (* execute_transaction ) (struct i2c_generic_hw_engine*,struct i2c_generic_transaction_attributes*) ;int /*<<< orphan*/  (* write_data ) (struct i2c_generic_hw_engine*,int /*<<< orphan*/ *,int) ;int /*<<< orphan*/  (* write_address ) (struct i2c_generic_hw_engine*,int /*<<< orphan*/ ) ;} ;
struct TYPE_5__ {int (* get_hw_buffer_available_size ) (struct i2c_hw_engine*) ;int (* wait_on_operation_result ) (struct i2c_hw_engine*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* get_transaction_timeout ) (struct i2c_hw_engine*,int) ;} ;

/* Variables and functions */
 struct i2c_generic_hw_engine* FROM_ENGINE (struct engine*) ; 
 int /*<<< orphan*/  I2CAUX_TRANSACTION_ACTION_I2C_READ ; 
 int /*<<< orphan*/  I2CAUX_TRANSACTION_ACTION_I2C_WRITE ; 
 scalar_t__ I2CAUX_TRANSACTION_READ ; 
 int /*<<< orphan*/  I2CAUX_TRANSACTION_STATUS_FAILED_INCOMPLETE ; 
 int /*<<< orphan*/  I2CAUX_TRANSACTION_STATUS_FAILED_INVALID_OPERATION ; 
 int /*<<< orphan*/  I2CAUX_TRANSACTION_STATUS_FAILED_NACK ; 
 int /*<<< orphan*/  I2CAUX_TRANSACTION_STATUS_FAILED_OPERATION ; 
 int /*<<< orphan*/  I2CAUX_TRANSACTION_STATUS_FAILED_TIMEOUT ; 
 int /*<<< orphan*/  I2CAUX_TRANSACTION_STATUS_SUCCEEDED ; 
 scalar_t__ I2CAUX_TRANSACTION_WRITE ; 
 int /*<<< orphan*/  I2C_CHANNEL_OPERATION_ENGINE_BUSY ; 
#define  I2C_CHANNEL_OPERATION_FAILED 131 
#define  I2C_CHANNEL_OPERATION_NO_RESPONSE 130 
#define  I2C_CHANNEL_OPERATION_SUCCEEDED 129 
#define  I2C_CHANNEL_OPERATION_TIMEOUT 128 
 int stub1 (struct i2c_hw_engine*) ; 
 int /*<<< orphan*/  stub2 (struct i2c_generic_hw_engine*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (struct i2c_generic_hw_engine*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stub4 (struct i2c_generic_hw_engine*,struct i2c_generic_transaction_attributes*) ; 
 int stub5 (struct i2c_hw_engine*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub6 (struct i2c_hw_engine*,int) ; 
 int /*<<< orphan*/  stub7 (struct i2c_generic_hw_engine*,int /*<<< orphan*/ *,int,int) ; 

bool dal_i2c_generic_hw_engine_submit_request(
	struct engine *engine,
	struct i2caux_transaction_request *i2caux_request,
	bool middle_of_transaction)
{
	struct i2c_generic_hw_engine *hw_engine = FROM_ENGINE(engine);

	struct i2c_hw_engine *base = &hw_engine->base;

	uint32_t max_payload_size =
		base->funcs->get_hw_buffer_available_size(base);

	bool initial_stop_bit = !middle_of_transaction;

	struct i2c_generic_transaction_attributes attributes;

	enum i2c_channel_operation_result operation_result =
		I2C_CHANNEL_OPERATION_FAILED;

	bool result = false;

	/* setup transaction initial properties */

	uint8_t address = i2caux_request->payload.address;
	uint8_t *current_payload = i2caux_request->payload.data;
	uint32_t remaining_payload_size = i2caux_request->payload.length;

	bool first_iteration = true;

	if (i2caux_request->operation == I2CAUX_TRANSACTION_READ)
		attributes.action = I2CAUX_TRANSACTION_ACTION_I2C_READ;
	else if (i2caux_request->operation == I2CAUX_TRANSACTION_WRITE)
		attributes.action = I2CAUX_TRANSACTION_ACTION_I2C_WRITE;
	else {
		i2caux_request->status =
			I2CAUX_TRANSACTION_STATUS_FAILED_INVALID_OPERATION;
		return false;
	}

	/* Do batch transaction.
	 * Divide read/write data into payloads which fit HW buffer size.
	 * 1. Single transaction:
	 *    start_bit = 1, stop_bit depends on session state, ack_on_read = 0;
	 * 2. Start of batch transaction:
	 *    start_bit = 1, stop_bit = 0, ack_on_read = 1;
	 * 3. Middle of batch transaction:
	 *    start_bit = 0, stop_bit = 0, ack_on_read = 1;
	 * 4. End of batch transaction:
	 *    start_bit = 0, stop_bit depends on session state, ack_on_read = 0.
	 * Session stop bit is set if 'middle_of_transaction' = 0. */

	while (remaining_payload_size) {
		uint32_t current_transaction_size;
		uint32_t current_payload_size;

		bool last_iteration;
		bool stop_bit;

		/* Calculate current transaction size and payload size.
		 * Transaction size = total number of bytes in transaction,
		 * including slave's address;
		 * Payload size = number of data bytes in transaction. */

		if (first_iteration) {
			/* In the first sub-transaction we send slave's address
			 * thus we need to reserve one byte for it */
			current_transaction_size =
			(remaining_payload_size > max_payload_size - 1) ?
				max_payload_size :
				remaining_payload_size + 1;

			current_payload_size = current_transaction_size - 1;
		} else {
			/* Second and further sub-transactions will have
			 * entire buffer reserved for data */
			current_transaction_size =
				(remaining_payload_size > max_payload_size) ?
				max_payload_size :
				remaining_payload_size;

			current_payload_size = current_transaction_size;
		}

		last_iteration =
			(remaining_payload_size == current_payload_size);

		stop_bit = last_iteration ? initial_stop_bit : false;

		/* write slave device address */

		if (first_iteration)
			hw_engine->funcs->write_address(hw_engine, address);

		/* write current portion of data, if requested */

		if (i2caux_request->operation == I2CAUX_TRANSACTION_WRITE)
			hw_engine->funcs->write_data(
				hw_engine,
				current_payload,
				current_payload_size);

		/* execute transaction */

		attributes.start_bit = first_iteration;
		attributes.stop_bit = stop_bit;
		attributes.last_read = last_iteration;
		attributes.transaction_size = current_transaction_size;

		hw_engine->funcs->execute_transaction(hw_engine, &attributes);

		/* wait until transaction is processed; if it fails - quit */

		operation_result = base->funcs->wait_on_operation_result(
			base,
			base->funcs->get_transaction_timeout(
				base, current_transaction_size),
			I2C_CHANNEL_OPERATION_ENGINE_BUSY);

		if (operation_result != I2C_CHANNEL_OPERATION_SUCCEEDED)
			break;

		/* read current portion of data, if requested */

		/* the read offset should be 1 for first sub-transaction,
		 * and 0 for any next one */

		if (i2caux_request->operation == I2CAUX_TRANSACTION_READ)
			hw_engine->funcs->read_data(hw_engine, current_payload,
				current_payload_size, first_iteration ? 1 : 0);

		/* update loop variables */

		first_iteration = false;
		current_payload += current_payload_size;
		remaining_payload_size -= current_payload_size;
	}

	/* update transaction status */

	switch (operation_result) {
	case I2C_CHANNEL_OPERATION_SUCCEEDED:
		i2caux_request->status =
			I2CAUX_TRANSACTION_STATUS_SUCCEEDED;
		result = true;
	break;
	case I2C_CHANNEL_OPERATION_NO_RESPONSE:
		i2caux_request->status =
			I2CAUX_TRANSACTION_STATUS_FAILED_NACK;
	break;
	case I2C_CHANNEL_OPERATION_TIMEOUT:
		i2caux_request->status =
			I2CAUX_TRANSACTION_STATUS_FAILED_TIMEOUT;
	break;
	case I2C_CHANNEL_OPERATION_FAILED:
		i2caux_request->status =
			I2CAUX_TRANSACTION_STATUS_FAILED_INCOMPLETE;
	break;
	default:
		i2caux_request->status =
			I2CAUX_TRANSACTION_STATUS_FAILED_OPERATION;
	}

	return result;
}