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
struct ddc_service {int transaction_type; } ;

/* Variables and functions */
#define  DDC_TRANSACTION_TYPE_I2C_OVER_AUX 130 
#define  DDC_TRANSACTION_TYPE_I2C_OVER_AUX_RETRY_DEFER 129 
#define  DDC_TRANSACTION_TYPE_I2C_OVER_AUX_WITH_DEFER 128 

bool dal_ddc_service_is_in_aux_transaction_mode(struct ddc_service *ddc)
{
	switch (ddc->transaction_type) {
	case DDC_TRANSACTION_TYPE_I2C_OVER_AUX:
	case DDC_TRANSACTION_TYPE_I2C_OVER_AUX_WITH_DEFER:
	case DDC_TRANSACTION_TYPE_I2C_OVER_AUX_RETRY_DEFER:
		return true;
	default:
		break;
	}
	return false;
}