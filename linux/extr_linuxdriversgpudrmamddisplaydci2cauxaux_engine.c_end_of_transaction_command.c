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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_2__ {scalar_t__ address_space; int /*<<< orphan*/ * data; scalar_t__ length; int /*<<< orphan*/  address; } ;
struct i2caux_transaction_request {scalar_t__ operation; TYPE_1__ payload; } ;
struct aux_engine {int dummy; } ;

/* Variables and functions */
 scalar_t__ I2CAUX_TRANSACTION_ADDRESS_SPACE_I2C ; 
 scalar_t__ I2CAUX_TRANSACTION_READ ; 
 int read_command (struct aux_engine*,struct i2caux_transaction_request*,int) ; 
 int write_command (struct aux_engine*,struct i2caux_transaction_request*,int) ; 

__attribute__((used)) static bool end_of_transaction_command(
	struct aux_engine *engine,
	struct i2caux_transaction_request *request)
{
	struct i2caux_transaction_request dummy_request;
	uint8_t dummy_data;

	/* [tcheng] We only need to send the stop (read with MOT = 0)
	 * for I2C-over-Aux, not native AUX */

	if (request->payload.address_space !=
		I2CAUX_TRANSACTION_ADDRESS_SPACE_I2C)
		return false;

	dummy_request.operation = request->operation;
	dummy_request.payload.address_space = request->payload.address_space;
	dummy_request.payload.address = request->payload.address;

	/*
	 * Add a dummy byte due to some receiver quirk
	 * where one byte is sent along with MOT = 0.
	 * Ideally this should be 0.
	 */

	dummy_request.payload.length = 0;
	dummy_request.payload.data = &dummy_data;

	if (request->operation == I2CAUX_TRANSACTION_READ)
		return read_command(engine, &dummy_request, false);
	else
		return write_command(engine, &dummy_request, false);

	/* according Syed, it does not need now DoDummyMOT */
}