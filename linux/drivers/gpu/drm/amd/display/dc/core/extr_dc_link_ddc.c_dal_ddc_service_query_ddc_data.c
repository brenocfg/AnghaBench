#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
struct i2c_payloads {int dummy; } ;
struct i2c_command {int /*<<< orphan*/  number_of_payloads; int /*<<< orphan*/  speed; int /*<<< orphan*/  engine; int /*<<< orphan*/  payloads; } ;
struct ddc_service {int /*<<< orphan*/  link; TYPE_3__* ctx; } ;
struct aux_payload {int i2c_over_aux; int write; int mot; int address; int length; int /*<<< orphan*/  defer_delay; int /*<<< orphan*/ * reply; int /*<<< orphan*/ * data; } ;
struct TYPE_7__ {TYPE_2__* dc; } ;
struct TYPE_5__ {int /*<<< orphan*/  i2c_speed_in_khz; } ;
struct TYPE_6__ {TYPE_1__ caps; } ;

/* Variables and functions */
 int /*<<< orphan*/  DDC_I2C_COMMAND_ENGINE ; 
 int DEFAULT_AUX_MAX_DATA_SIZE ; 
 int EDID_SEGMENT_SIZE ; 
 int /*<<< orphan*/  dal_ddc_i2c_payloads_add (struct i2c_payloads*,int,int,int /*<<< orphan*/ *,int) ; 
 struct i2c_payloads* dal_ddc_i2c_payloads_create (TYPE_3__*,int) ; 
 int /*<<< orphan*/  dal_ddc_i2c_payloads_destroy (struct i2c_payloads**) ; 
 int /*<<< orphan*/  dal_ddc_i2c_payloads_get (struct i2c_payloads*) ; 
 int /*<<< orphan*/  dal_ddc_i2c_payloads_get_count (struct i2c_payloads*) ; 
 scalar_t__ dal_ddc_service_is_in_aux_transaction_mode (struct ddc_service*) ; 
 int dc_link_aux_transfer_with_retries (struct ddc_service*,struct aux_payload*) ; 
 int dm_helpers_submit_i2c (TYPE_3__*,int /*<<< orphan*/ ,struct i2c_command*) ; 
 int /*<<< orphan*/  get_defer_delay (struct ddc_service*) ; 

bool dal_ddc_service_query_ddc_data(
	struct ddc_service *ddc,
	uint32_t address,
	uint8_t *write_buf,
	uint32_t write_size,
	uint8_t *read_buf,
	uint32_t read_size)
{
	bool ret;
	uint32_t payload_size =
		dal_ddc_service_is_in_aux_transaction_mode(ddc) ?
			DEFAULT_AUX_MAX_DATA_SIZE : EDID_SEGMENT_SIZE;

	uint32_t write_payloads =
		(write_size + payload_size - 1) / payload_size;

	uint32_t read_payloads =
		(read_size + payload_size - 1) / payload_size;

	uint32_t payloads_num = write_payloads + read_payloads;

	if (write_size > EDID_SEGMENT_SIZE || read_size > EDID_SEGMENT_SIZE)
		return false;

	/*TODO: len of payload data for i2c and aux is uint8!!!!,
	 *  but we want to read 256 over i2c!!!!*/
	if (dal_ddc_service_is_in_aux_transaction_mode(ddc)) {
		struct aux_payload write_payload = {
			.i2c_over_aux = true,
			.write = true,
			.mot = true,
			.address = address,
			.length = write_size,
			.data = write_buf,
			.reply = NULL,
			.defer_delay = get_defer_delay(ddc),
		};

		struct aux_payload read_payload = {
			.i2c_over_aux = true,
			.write = false,
			.mot = false,
			.address = address,
			.length = read_size,
			.data = read_buf,
			.reply = NULL,
			.defer_delay = get_defer_delay(ddc),
		};

		ret = dc_link_aux_transfer_with_retries(ddc, &write_payload);

		if (!ret)
			return false;

		ret = dc_link_aux_transfer_with_retries(ddc, &read_payload);
	} else {
		struct i2c_payloads *payloads =
			dal_ddc_i2c_payloads_create(ddc->ctx, payloads_num);

		struct i2c_command command = {
			.payloads = dal_ddc_i2c_payloads_get(payloads),
			.number_of_payloads = 0,
			.engine = DDC_I2C_COMMAND_ENGINE,
			.speed = ddc->ctx->dc->caps.i2c_speed_in_khz };

		dal_ddc_i2c_payloads_add(
			payloads, address, write_size, write_buf, true);

		dal_ddc_i2c_payloads_add(
			payloads, address, read_size, read_buf, false);

		command.number_of_payloads =
			dal_ddc_i2c_payloads_get_count(payloads);

		ret = dm_helpers_submit_i2c(
				ddc->ctx,
				ddc->link,
				&command);

		dal_ddc_i2c_payloads_destroy(&payloads);
	}

	return ret;
}