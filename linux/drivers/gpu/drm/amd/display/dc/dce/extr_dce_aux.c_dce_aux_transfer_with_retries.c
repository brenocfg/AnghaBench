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
typedef  int /*<<< orphan*/  uint8_t ;
struct ddc_service {int dummy; } ;
struct aux_payload {int length; int /*<<< orphan*/ * reply; int /*<<< orphan*/  write; } ;
typedef  enum aux_channel_operation_result { ____Placeholder_aux_channel_operation_result } aux_channel_operation_result ;

/* Variables and functions */
#define  AUX_CHANNEL_OPERATION_FAILED_HPD_DISCON 139 
#define  AUX_CHANNEL_OPERATION_FAILED_INVALID_REPLY 138 
#define  AUX_CHANNEL_OPERATION_FAILED_REASON_UNKNOWN 137 
#define  AUX_CHANNEL_OPERATION_FAILED_TIMEOUT 136 
#define  AUX_CHANNEL_OPERATION_SUCCEEDED 135 
 int AUX_MAX_DEFER_RETRIES ; 
 int AUX_MAX_I2C_DEFER_RETRIES ; 
 int AUX_MAX_INVALID_REPLY_RETRIES ; 
 int AUX_MAX_RETRIES ; 
 int AUX_MAX_TIMEOUT_RETRIES ; 
#define  AUX_TRANSACTION_REPLY_AUX_ACK 134 
#define  AUX_TRANSACTION_REPLY_AUX_DEFER 133 
#define  AUX_TRANSACTION_REPLY_AUX_NACK 132 
#define  AUX_TRANSACTION_REPLY_HPD_DISCON 131 
#define  AUX_TRANSACTION_REPLY_I2C_DEFER 130 
#define  AUX_TRANSACTION_REPLY_I2C_OVER_AUX_DEFER 129 
#define  AUX_TRANSACTION_REPLY_I2C_OVER_AUX_NACK 128 
 int dce_aux_transfer_raw (struct ddc_service*,struct aux_payload*,int*) ; 
 int /*<<< orphan*/  udelay (int) ; 

bool dce_aux_transfer_with_retries(struct ddc_service *ddc,
		struct aux_payload *payload)
{
	int i, ret = 0;
	uint8_t reply;
	bool payload_reply = true;
	enum aux_channel_operation_result operation_result;
	int aux_ack_retries = 0,
		aux_defer_retries = 0,
		aux_i2c_defer_retries = 0,
		aux_timeout_retries = 0,
		aux_invalid_reply_retries = 0;

	if (!payload->reply) {
		payload_reply = false;
		payload->reply = &reply;
	}

	for (i = 0; i < AUX_MAX_RETRIES; i++) {
		ret = dce_aux_transfer_raw(ddc, payload, &operation_result);
		switch (operation_result) {
		case AUX_CHANNEL_OPERATION_SUCCEEDED:
			aux_timeout_retries = 0;
			aux_invalid_reply_retries = 0;

			switch (*payload->reply) {
			case AUX_TRANSACTION_REPLY_AUX_ACK:
				if (!payload->write && payload->length != ret) {
					if (++aux_ack_retries >= AUX_MAX_RETRIES)
						goto fail;
					else
						udelay(300);
				} else
					return true;
			break;

			case AUX_TRANSACTION_REPLY_AUX_DEFER:
			case AUX_TRANSACTION_REPLY_I2C_OVER_AUX_NACK:
			case AUX_TRANSACTION_REPLY_I2C_OVER_AUX_DEFER:
				if (++aux_defer_retries >= AUX_MAX_DEFER_RETRIES)
					goto fail;
				break;

			case AUX_TRANSACTION_REPLY_I2C_DEFER:
				aux_defer_retries = 0;
				if (++aux_i2c_defer_retries >= AUX_MAX_I2C_DEFER_RETRIES)
					goto fail;
				break;

			case AUX_TRANSACTION_REPLY_AUX_NACK:
			case AUX_TRANSACTION_REPLY_HPD_DISCON:
			default:
				goto fail;
			}
			break;

		case AUX_CHANNEL_OPERATION_FAILED_INVALID_REPLY:
			if (++aux_invalid_reply_retries >= AUX_MAX_INVALID_REPLY_RETRIES)
				goto fail;
			else
				udelay(400);
			break;

		case AUX_CHANNEL_OPERATION_FAILED_TIMEOUT:
			if (++aux_timeout_retries >= AUX_MAX_TIMEOUT_RETRIES)
				goto fail;
			else {
				/*
				 * DP 1.4, 2.8.2:  AUX Transaction Response/Reply Timeouts
				 * According to the DP spec there should be 3 retries total
				 * with a 400us wait inbetween each. Hardware already waits
				 * for 550us therefore no wait is required here.
				 */
			}
			break;

		case AUX_CHANNEL_OPERATION_FAILED_HPD_DISCON:
		case AUX_CHANNEL_OPERATION_FAILED_REASON_UNKNOWN:
		default:
			goto fail;
		}
	}

fail:
	if (!payload_reply)
		payload->reply = NULL;
	return false;
}