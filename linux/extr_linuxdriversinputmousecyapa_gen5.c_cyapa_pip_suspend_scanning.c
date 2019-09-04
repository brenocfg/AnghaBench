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
struct cyapa {int dummy; } ;
typedef  int /*<<< orphan*/  resp_data ;
typedef  int /*<<< orphan*/  cmd ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  VALID_CMD_RESP_HEADER (int*,int) ; 
 int /*<<< orphan*/  cyapa_empty_pip_output_data (struct cyapa*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int cyapa_i2c_pip_cmd_irq_sync (struct cyapa*,int*,int,int*,int*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cyapa_sort_tsg_pip_app_resp_data ; 

int cyapa_pip_suspend_scanning(struct cyapa *cyapa)
{
	u8 cmd[] = { 0x04, 0x00, 0x05, 0x00, 0x2f, 0x00, 0x03 };
	u8 resp_data[6];
	int resp_len;
	int error;

	/* Try to dump all buffered data before doing command. */
	cyapa_empty_pip_output_data(cyapa, NULL, NULL, NULL);

	resp_len = sizeof(resp_data);
	error = cyapa_i2c_pip_cmd_irq_sync(cyapa,
			cmd, sizeof(cmd),
			resp_data, &resp_len,
			500, cyapa_sort_tsg_pip_app_resp_data, true);
	if (error || !VALID_CMD_RESP_HEADER(resp_data, 0x03))
		return -EINVAL;

	/* Try to dump all buffered data when suspending scanning. */
	cyapa_empty_pip_output_data(cyapa, NULL, NULL, NULL);

	return 0;
}