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
typedef  int uint8_t ;
typedef  int uint32_t ;
struct aux_reply_transaction_data {void* status; int /*<<< orphan*/  data; int /*<<< orphan*/  length; } ;
struct aux_engine {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_CRITICAL (int) ; 
 void* AUX_CHANNEL_OPERATION_FAILED_HPD_DISCON ; 
 int AUX_SW_STATUS__AUX_SW_HPD_DISCON_MASK ; 
 void* AUX_TRANSACTION_REPLY_AUX_ACK ; 
 void* AUX_TRANSACTION_REPLY_AUX_DEFER ; 
 void* AUX_TRANSACTION_REPLY_AUX_NACK ; 
 void* AUX_TRANSACTION_REPLY_I2C_DEFER ; 
 void* AUX_TRANSACTION_REPLY_I2C_NACK ; 
 void* AUX_TRANSACTION_REPLY_INVALID ; 
 int read_channel_reply (struct aux_engine*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int*) ; 

__attribute__((used)) static void process_channel_reply(
	struct aux_engine *engine,
	struct aux_reply_transaction_data *reply)
{
	int bytes_replied;
	uint8_t reply_result;
	uint32_t sw_status;

	bytes_replied = read_channel_reply(engine, reply->length, reply->data,
					   &reply_result, &sw_status);

	/* in case HPD is LOW, exit AUX transaction */
	if ((sw_status & AUX_SW_STATUS__AUX_SW_HPD_DISCON_MASK)) {
		reply->status = AUX_CHANNEL_OPERATION_FAILED_HPD_DISCON;
		return;
	}

	if (bytes_replied < 0) {
		/* Need to handle an error case...
		 * Hopefully, upper layer function won't call this function if
		 * the number of bytes in the reply was 0, because there was
		 * surely an error that was asserted that should have been
		 * handled for hot plug case, this could happens
		 */
		if (!(sw_status & AUX_SW_STATUS__AUX_SW_HPD_DISCON_MASK)) {
			reply->status = AUX_TRANSACTION_REPLY_INVALID;
			ASSERT_CRITICAL(false);
			return;
		}
	} else {

		switch (reply_result) {
		case 0: /* ACK */
			reply->status = AUX_TRANSACTION_REPLY_AUX_ACK;
		break;
		case 1: /* NACK */
			reply->status = AUX_TRANSACTION_REPLY_AUX_NACK;
		break;
		case 2: /* DEFER */
			reply->status = AUX_TRANSACTION_REPLY_AUX_DEFER;
		break;
		case 4: /* AUX ACK / I2C NACK */
			reply->status = AUX_TRANSACTION_REPLY_I2C_NACK;
		break;
		case 8: /* AUX ACK / I2C DEFER */
			reply->status = AUX_TRANSACTION_REPLY_I2C_DEFER;
		break;
		default:
			reply->status = AUX_TRANSACTION_REPLY_INVALID;
		}
	}
}