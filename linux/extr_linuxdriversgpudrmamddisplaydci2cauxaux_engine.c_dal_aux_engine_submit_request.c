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
struct i2caux_transaction_request {int operation; } ;
struct engine {int dummy; } ;
struct aux_engine {int dummy; } ;

/* Variables and functions */
 struct aux_engine* FROM_ENGINE (struct engine*) ; 
#define  I2CAUX_TRANSACTION_READ 129 
#define  I2CAUX_TRANSACTION_WRITE 128 
 int /*<<< orphan*/  end_of_transaction_command (struct aux_engine*,struct i2caux_transaction_request*) ; 
 int read_command (struct aux_engine*,struct i2caux_transaction_request*,int) ; 
 int write_command (struct aux_engine*,struct i2caux_transaction_request*,int) ; 

bool dal_aux_engine_submit_request(
	struct engine *engine,
	struct i2caux_transaction_request *request,
	bool middle_of_transaction)
{
	struct aux_engine *aux_engine = FROM_ENGINE(engine);

	bool result;
	bool mot_used = true;

	switch (request->operation) {
	case I2CAUX_TRANSACTION_READ:
		result = read_command(aux_engine, request, mot_used);
	break;
	case I2CAUX_TRANSACTION_WRITE:
		result = write_command(aux_engine, request, mot_used);
	break;
	default:
		result = false;
	}

	/* [tcheng]
	 * need to send stop for the last transaction to free up the AUX
	 * if the above command fails, this would be the last transaction */

	if (!middle_of_transaction || !result)
		end_of_transaction_command(aux_engine, request);

	/* mask AUX interrupt */

	return result;
}