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
struct drm_dp_aux_msg {int size; int request; int /*<<< orphan*/  reply; int /*<<< orphan*/  buffer; int /*<<< orphan*/  address; } ;
struct drm_dp_aux {int dummy; } ;
struct aux_payload {int length; int i2c_over_aux; int write; int mot; scalar_t__ defer_delay; int /*<<< orphan*/ * reply; int /*<<< orphan*/  data; int /*<<< orphan*/  address; } ;
typedef  int ssize_t ;
typedef  enum aux_channel_operation_result { ____Placeholder_aux_channel_operation_result } aux_channel_operation_result ;
struct TYPE_2__ {int /*<<< orphan*/  ddc_service; } ;

/* Variables and functions */
#define  AUX_CHANNEL_OPERATION_FAILED_HPD_DISCON 132 
#define  AUX_CHANNEL_OPERATION_FAILED_INVALID_REPLY 131 
#define  AUX_CHANNEL_OPERATION_FAILED_REASON_UNKNOWN 130 
#define  AUX_CHANNEL_OPERATION_FAILED_TIMEOUT 129 
#define  AUX_CHANNEL_OPERATION_SUCCEEDED 128 
 int DP_AUX_I2C_MOT ; 
 int DP_AUX_I2C_READ ; 
 int DP_AUX_NATIVE_WRITE ; 
 int E2BIG ; 
 int EBUSY ; 
 int EIO ; 
 int ETIMEDOUT ; 
 TYPE_1__* TO_DM_AUX (struct drm_dp_aux*) ; 
 scalar_t__ WARN_ON (int) ; 
 int dc_link_aux_transfer_raw (int /*<<< orphan*/ ,struct aux_payload*,int*) ; 

__attribute__((used)) static ssize_t dm_dp_aux_transfer(struct drm_dp_aux *aux,
				  struct drm_dp_aux_msg *msg)
{
	ssize_t result = 0;
	struct aux_payload payload;
	enum aux_channel_operation_result operation_result;

	if (WARN_ON(msg->size > 16))
		return -E2BIG;

	payload.address = msg->address;
	payload.data = msg->buffer;
	payload.length = msg->size;
	payload.reply = &msg->reply;
	payload.i2c_over_aux = (msg->request & DP_AUX_NATIVE_WRITE) == 0;
	payload.write = (msg->request & DP_AUX_I2C_READ) == 0;
	payload.mot = (msg->request & DP_AUX_I2C_MOT) != 0;
	payload.defer_delay = 0;

	result = dc_link_aux_transfer_raw(TO_DM_AUX(aux)->ddc_service, &payload,
				      &operation_result);

	if (payload.write)
		result = msg->size;

	if (result < 0)
		switch (operation_result) {
		case AUX_CHANNEL_OPERATION_SUCCEEDED:
			break;
		case AUX_CHANNEL_OPERATION_FAILED_HPD_DISCON:
		case AUX_CHANNEL_OPERATION_FAILED_REASON_UNKNOWN:
			result = -EIO;
			break;
		case AUX_CHANNEL_OPERATION_FAILED_INVALID_REPLY:
			result = -EBUSY;
			break;
		case AUX_CHANNEL_OPERATION_FAILED_TIMEOUT:
			result = -ETIMEDOUT;
			break;
		}

	return result;
}