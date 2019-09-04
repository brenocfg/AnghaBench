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
struct drm_dp_aux_msg {int size; int request; int /*<<< orphan*/  buffer; int /*<<< orphan*/  reply; int /*<<< orphan*/  address; } ;
struct drm_dp_aux {int dummy; } ;
typedef  int ssize_t ;
typedef  enum i2caux_transaction_action { ____Placeholder_i2caux_transaction_action } i2caux_transaction_action ;
typedef  enum aux_transaction_type { ____Placeholder_aux_transaction_type } aux_transaction_type ;
struct TYPE_2__ {int /*<<< orphan*/  ddc_service; } ;

/* Variables and functions */
 int AUX_TRANSACTION_TYPE_DP ; 
 int AUX_TRANSACTION_TYPE_I2C ; 
 int DP_AUX_I2C_MOT ; 
#define  DP_AUX_I2C_READ 131 
#define  DP_AUX_I2C_WRITE 130 
#define  DP_AUX_NATIVE_READ 129 
#define  DP_AUX_NATIVE_WRITE 128 
 int E2BIG ; 
 int EINVAL ; 
 int EIO ; 
 int I2CAUX_TRANSACTION_ACTION_DP_READ ; 
 int I2CAUX_TRANSACTION_ACTION_DP_WRITE ; 
 int I2CAUX_TRANSACTION_ACTION_I2C_READ ; 
 int I2CAUX_TRANSACTION_ACTION_I2C_READ_MOT ; 
 int I2CAUX_TRANSACTION_ACTION_I2C_WRITE ; 
 int I2CAUX_TRANSACTION_ACTION_I2C_WRITE_MOT ; 
 TYPE_1__* TO_DM_AUX (struct drm_dp_aux*) ; 
 scalar_t__ WARN_ON (int) ; 
 int dc_link_aux_transfer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int) ; 

__attribute__((used)) static ssize_t dm_dp_aux_transfer(struct drm_dp_aux *aux,
				  struct drm_dp_aux_msg *msg)
{
	ssize_t result = 0;
	enum i2caux_transaction_action action;
	enum aux_transaction_type type;

	if (WARN_ON(msg->size > 16))
		return -E2BIG;

	switch (msg->request & ~DP_AUX_I2C_MOT) {
	case DP_AUX_NATIVE_READ:
		type = AUX_TRANSACTION_TYPE_DP;
		action = I2CAUX_TRANSACTION_ACTION_DP_READ;

		result = dc_link_aux_transfer(TO_DM_AUX(aux)->ddc_service,
					      msg->address,
					      &msg->reply,
					      msg->buffer,
					      msg->size,
					      type,
					      action);
		break;
	case DP_AUX_NATIVE_WRITE:
		type = AUX_TRANSACTION_TYPE_DP;
		action = I2CAUX_TRANSACTION_ACTION_DP_WRITE;

		dc_link_aux_transfer(TO_DM_AUX(aux)->ddc_service,
				     msg->address,
				     &msg->reply,
				     msg->buffer,
				     msg->size,
				     type,
				     action);
		result = msg->size;
		break;
	case DP_AUX_I2C_READ:
		type = AUX_TRANSACTION_TYPE_I2C;
		if (msg->request & DP_AUX_I2C_MOT)
			action = I2CAUX_TRANSACTION_ACTION_I2C_READ_MOT;
		else
			action = I2CAUX_TRANSACTION_ACTION_I2C_READ;

		result = dc_link_aux_transfer(TO_DM_AUX(aux)->ddc_service,
					      msg->address,
					      &msg->reply,
					      msg->buffer,
					      msg->size,
					      type,
					      action);
		break;
	case DP_AUX_I2C_WRITE:
		type = AUX_TRANSACTION_TYPE_I2C;
		if (msg->request & DP_AUX_I2C_MOT)
			action = I2CAUX_TRANSACTION_ACTION_I2C_WRITE_MOT;
		else
			action = I2CAUX_TRANSACTION_ACTION_I2C_WRITE;

		dc_link_aux_transfer(TO_DM_AUX(aux)->ddc_service,
				     msg->address,
				     &msg->reply,
				     msg->buffer,
				     msg->size,
				     type,
				     action);
		result = msg->size;
		break;
	default:
		return -EINVAL;
	}

#ifdef TRACE_DPCD
	log_dpcd(msg->request,
		 msg->address,
		 msg->buffer,
		 msg->size,
		 r == DDC_RESULT_SUCESSFULL);
#endif

	if (result < 0) /* DC doesn't know about kernel error codes */
		result = -EIO;

	return result;
}