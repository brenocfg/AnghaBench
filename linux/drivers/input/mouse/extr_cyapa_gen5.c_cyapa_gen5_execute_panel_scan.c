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
typedef  int /*<<< orphan*/  u8 ;
struct pip_app_cmd_head {int /*<<< orphan*/  cmd_code; int /*<<< orphan*/  report_id; int /*<<< orphan*/  length; int /*<<< orphan*/  addr; } ;
struct cyapa {int dummy; } ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  resp_data ;
typedef  int /*<<< orphan*/  cmd ;

/* Variables and functions */
 int EAGAIN ; 
 int /*<<< orphan*/  GEN5_CMD_EXECUTE_PANEL_SCAN ; 
 int /*<<< orphan*/  PIP_APP_CMD_REPORT_ID ; 
 int /*<<< orphan*/  PIP_CMD_COMPLETE_SUCCESS (int /*<<< orphan*/ *) ; 
 int PIP_OUTPUT_REPORT_ADDR ; 
 int /*<<< orphan*/  VALID_CMD_RESP_HEADER (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int cyapa_i2c_pip_cmd_irq_sync (struct cyapa*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cyapa_sort_tsg_pip_app_resp_data ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  put_unaligned_le16 (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t cyapa_gen5_execute_panel_scan(struct cyapa *cyapa)
{
	struct pip_app_cmd_head *app_cmd_head;
	u8 cmd[7];
	u8 resp_data[6];
	int resp_len;
	int error;

	memset(cmd, 0, sizeof(cmd));
	app_cmd_head = (struct pip_app_cmd_head *)cmd;
	put_unaligned_le16(PIP_OUTPUT_REPORT_ADDR, &app_cmd_head->addr);
	put_unaligned_le16(sizeof(cmd) - 2, &app_cmd_head->length);
	app_cmd_head->report_id = PIP_APP_CMD_REPORT_ID;
	app_cmd_head->cmd_code = GEN5_CMD_EXECUTE_PANEL_SCAN;
	resp_len = sizeof(resp_data);
	error = cyapa_i2c_pip_cmd_irq_sync(cyapa,
			cmd, sizeof(cmd),
			resp_data, &resp_len,
			500, cyapa_sort_tsg_pip_app_resp_data, true);
	if (error || resp_len != sizeof(resp_data) ||
			!VALID_CMD_RESP_HEADER(resp_data,
				GEN5_CMD_EXECUTE_PANEL_SCAN) ||
			!PIP_CMD_COMPLETE_SUCCESS(resp_data))
		return error ? error : -EAGAIN;

	return 0;
}