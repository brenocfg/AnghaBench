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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  scalar_t__ u16 ;
struct pip_app_cmd_head {int /*<<< orphan*/  cmd_code; int /*<<< orphan*/  report_id; int /*<<< orphan*/  length; int /*<<< orphan*/  addr; scalar_t__ parameter_data; } ;
struct gen5_app_set_parameter_data {int parameter_id; int parameter_size; int /*<<< orphan*/  value; } ;
struct cyapa {int dummy; } ;
typedef  int /*<<< orphan*/  resp_data ;

/* Variables and functions */
 int CYAPA_TSG_MAX_CMD_SIZE ; 
 int EINVAL ; 
 int /*<<< orphan*/  GEN5_CMD_SET_PARAMETER ; 
#define  GEN5_PARAMETER_ACT_INTERVL_ID 130 
 int GEN5_PARAMETER_ACT_INTERVL_SIZE ; 
#define  GEN5_PARAMETER_ACT_LFT_INTERVL_ID 129 
 int GEN5_PARAMETER_ACT_LFT_INTERVL_SIZE ; 
#define  GEN5_PARAMETER_LP_INTRVL_ID 128 
 int GEN5_PARAMETER_LP_INTRVL_SIZE ; 
 int /*<<< orphan*/  PIP_APP_CMD_REPORT_ID ; 
 int PIP_OUTPUT_REPORT_ADDR ; 
 int /*<<< orphan*/  VALID_CMD_RESP_HEADER (int*,int /*<<< orphan*/ ) ; 
 int cyapa_i2c_pip_cmd_irq_sync (struct cyapa*,int*,int,int*,int*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cyapa_sort_tsg_pip_app_resp_data ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  put_unaligned_le16 (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_unaligned_le32 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cyapa_gen5_set_interval_time(struct cyapa *cyapa,
		u8 parameter_id, u16 interval_time)
{
	struct pip_app_cmd_head *app_cmd_head;
	struct gen5_app_set_parameter_data *parameter_data;
	u8 cmd[CYAPA_TSG_MAX_CMD_SIZE];
	int cmd_len;
	u8 resp_data[7];
	int resp_len;
	u8 parameter_size;
	int error;

	memset(cmd, 0, CYAPA_TSG_MAX_CMD_SIZE);
	app_cmd_head = (struct pip_app_cmd_head *)cmd;
	parameter_data = (struct gen5_app_set_parameter_data *)
			 app_cmd_head->parameter_data;
	cmd_len = sizeof(struct pip_app_cmd_head) +
		  sizeof(struct gen5_app_set_parameter_data);

	switch (parameter_id) {
	case GEN5_PARAMETER_ACT_INTERVL_ID:
		parameter_size = GEN5_PARAMETER_ACT_INTERVL_SIZE;
		break;
	case GEN5_PARAMETER_ACT_LFT_INTERVL_ID:
		parameter_size = GEN5_PARAMETER_ACT_LFT_INTERVL_SIZE;
		break;
	case GEN5_PARAMETER_LP_INTRVL_ID:
		parameter_size = GEN5_PARAMETER_LP_INTRVL_SIZE;
		break;
	default:
		return -EINVAL;
	}

	put_unaligned_le16(PIP_OUTPUT_REPORT_ADDR, &app_cmd_head->addr);
	/*
	 * Don't include unused parameter value bytes and
	 * 2 bytes register address.
	 */
	put_unaligned_le16(cmd_len - (4 - parameter_size) - 2,
			   &app_cmd_head->length);
	app_cmd_head->report_id = PIP_APP_CMD_REPORT_ID;
	app_cmd_head->cmd_code = GEN5_CMD_SET_PARAMETER;
	parameter_data->parameter_id = parameter_id;
	parameter_data->parameter_size = parameter_size;
	put_unaligned_le32((u32)interval_time, &parameter_data->value);
	resp_len = sizeof(resp_data);
	error = cyapa_i2c_pip_cmd_irq_sync(cyapa, cmd, cmd_len,
			resp_data, &resp_len,
			500, cyapa_sort_tsg_pip_app_resp_data, false);
	if (error || resp_data[5] != parameter_id ||
		resp_data[6] != parameter_size ||
		!VALID_CMD_RESP_HEADER(resp_data, GEN5_CMD_SET_PARAMETER))
		return error < 0 ? error : -EINVAL;

	return 0;
}