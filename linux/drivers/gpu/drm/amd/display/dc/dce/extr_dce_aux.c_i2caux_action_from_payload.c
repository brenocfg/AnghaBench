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
struct aux_payload {scalar_t__ write; scalar_t__ mot; scalar_t__ i2c_over_aux; } ;
typedef  enum i2caux_transaction_action { ____Placeholder_i2caux_transaction_action } i2caux_transaction_action ;

/* Variables and functions */
 int I2CAUX_TRANSACTION_ACTION_DP_READ ; 
 int I2CAUX_TRANSACTION_ACTION_DP_WRITE ; 
 int I2CAUX_TRANSACTION_ACTION_I2C_READ ; 
 int I2CAUX_TRANSACTION_ACTION_I2C_READ_MOT ; 
 int I2CAUX_TRANSACTION_ACTION_I2C_WRITE ; 
 int I2CAUX_TRANSACTION_ACTION_I2C_WRITE_MOT ; 

__attribute__((used)) static enum i2caux_transaction_action i2caux_action_from_payload(struct aux_payload *payload)
{
	if (payload->i2c_over_aux) {
		if (payload->write) {
			if (payload->mot)
				return I2CAUX_TRANSACTION_ACTION_I2C_WRITE_MOT;
			return I2CAUX_TRANSACTION_ACTION_I2C_WRITE;
		}
		if (payload->mot)
			return I2CAUX_TRANSACTION_ACTION_I2C_READ_MOT;
		return I2CAUX_TRANSACTION_ACTION_I2C_READ;
	}
	if (payload->write)
		return I2CAUX_TRANSACTION_ACTION_DP_WRITE;
	return I2CAUX_TRANSACTION_ACTION_DP_READ;
}