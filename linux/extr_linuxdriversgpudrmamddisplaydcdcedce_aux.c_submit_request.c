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
struct aux_engine {int dummy; } ;

/* Variables and functions */
#define  I2CAUX_TRANSACTION_READ 129 
#define  I2CAUX_TRANSACTION_WRITE 128 
 int /*<<< orphan*/  end_of_transaction_command (struct aux_engine*,struct i2caux_transaction_request*) ; 
 int read_command (struct aux_engine*,struct i2caux_transaction_request*,int) ; 
 int write_command (struct aux_engine*,struct i2caux_transaction_request*,int) ; 

__attribute__((used)) static bool submit_request(
	struct aux_engine *engine,
	struct i2caux_transaction_request *request,
	bool middle_of_transaction)
{

	bool result;
	bool mot_used = true;

	switch (request->operation) {
	case I2CAUX_TRANSACTION_READ:
		result = read_command(engine, request, mot_used);
	break;
	case I2CAUX_TRANSACTION_WRITE:
		result = write_command(engine, request, mot_used);
	break;
	default:
		result = false;
	}

	/* [tcheng]
	 * need to send stop for the last transaction to free up the AUX
	 * if the above command fails, this would be the last transaction
	 */

	if (!middle_of_transaction || !result)
		end_of_transaction_command(engine, request);

	/* mask AUX interrupt */

	return result;
}