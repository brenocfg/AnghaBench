#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* spidev; } ;
struct st95hf_context {TYPE_2__ spicontext; } ;
struct param_list {int param_offset; unsigned char new_param_val; } ;
struct device {int dummy; } ;
typedef  enum st95hf_cmd_list { ____Placeholder_st95hf_cmd_list } st95hf_cmd_list ;
struct TYPE_7__ {int cmd_len; int no_cmd_params; unsigned char cmd_id; scalar_t__ req; int /*<<< orphan*/  cmd_params; } ;
struct TYPE_5__ {struct device dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int MAX_CMD_LEN ; 
 unsigned char ST95HF_COMMAND_SEND ; 
 scalar_t__ SYNC ; 
 TYPE_4__* cmd_array ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,unsigned char) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,int /*<<< orphan*/ ,unsigned char) ; 
 int st95hf_spi_recv_response (TYPE_2__*,unsigned char*) ; 
 int st95hf_spi_send (TYPE_2__*,unsigned char*,int,scalar_t__) ; 

__attribute__((used)) static int st95hf_send_recv_cmd(struct st95hf_context *st95context,
				enum st95hf_cmd_list cmd,
				int no_modif,
				struct param_list *list_array,
				bool recv_res)
{
	unsigned char spi_cmd_buffer[MAX_CMD_LEN];
	int i, ret;
	struct device *dev = &st95context->spicontext.spidev->dev;

	if (cmd_array[cmd].cmd_len > MAX_CMD_LEN)
		return -EINVAL;
	if (cmd_array[cmd].no_cmd_params < no_modif)
		return -EINVAL;
	if (no_modif && !list_array)
		return -EINVAL;

	spi_cmd_buffer[0] = ST95HF_COMMAND_SEND;
	spi_cmd_buffer[1] = cmd_array[cmd].cmd_id;
	spi_cmd_buffer[2] = cmd_array[cmd].no_cmd_params;

	memcpy(&spi_cmd_buffer[3], cmd_array[cmd].cmd_params,
	       spi_cmd_buffer[2]);

	for (i = 0; i < no_modif; i++) {
		if (list_array[i].param_offset >= cmd_array[cmd].no_cmd_params)
			return -EINVAL;
		spi_cmd_buffer[3 + list_array[i].param_offset] =
						list_array[i].new_param_val;
	}

	ret = st95hf_spi_send(&st95context->spicontext,
			      spi_cmd_buffer,
			      cmd_array[cmd].cmd_len,
			      cmd_array[cmd].req);
	if (ret) {
		dev_err(dev, "st95hf_spi_send failed with error %d\n", ret);
		return ret;
	}

	if (cmd_array[cmd].req == SYNC && recv_res) {
		unsigned char st95hf_response_arr[2];

		ret = st95hf_spi_recv_response(&st95context->spicontext,
					       st95hf_response_arr);
		if (ret < 0) {
			dev_err(dev, "spi error from st95hf_spi_recv_response(), err = 0x%x\n",
				ret);
			return ret;
		}

		if (st95hf_response_arr[0]) {
			dev_err(dev, "st95hf error from st95hf_spi_recv_response(), err = 0x%x\n",
				st95hf_response_arr[0]);
			return -EIO;
		}
	}

	return 0;
}