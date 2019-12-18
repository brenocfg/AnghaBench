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
struct cyapa {int operational; scalar_t__ gen; int /*<<< orphan*/  state; } ;
typedef  int /*<<< orphan*/  resp_data ;
typedef  int /*<<< orphan*/  cmd ;

/* Variables and functions */
 scalar_t__ CYAPA_GEN5 ; 
 scalar_t__ CYAPA_GEN6 ; 
 int /*<<< orphan*/  CYAPA_STATE_GEN5_BL ; 
 int /*<<< orphan*/  CYAPA_STATE_GEN6_BL ; 
 int EAGAIN ; 
 int EINVAL ; 
 int /*<<< orphan*/  cyapa_empty_pip_output_data (struct cyapa*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int cyapa_i2c_pip_cmd_irq_sync (struct cyapa*,int*,int,int*,int*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cyapa_is_pip_app_mode (struct cyapa*) ; 
 scalar_t__ cyapa_is_pip_bl_mode (struct cyapa*) ; 
 int cyapa_poll_state (struct cyapa*,int) ; 
 int /*<<< orphan*/  cyapa_sort_pip_application_launch_data ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 

int cyapa_pip_bl_enter(struct cyapa *cyapa)
{
	u8 cmd[] = { 0x04, 0x00, 0x05, 0x00, 0x2F, 0x00, 0x01 };
	u8 resp_data[2];
	int resp_len;
	int error;

	error = cyapa_poll_state(cyapa, 500);
	if (error < 0)
		return error;

	/* Already in bootloader mode, Skipping exit. */
	if (cyapa_is_pip_bl_mode(cyapa))
		return 0;
	else if (!cyapa_is_pip_app_mode(cyapa))
		return -EINVAL;

	/* Try to dump all buffered report data before any send command. */
	cyapa_empty_pip_output_data(cyapa, NULL, NULL, NULL);

	/*
	 * Send bootloader enter command to trackpad device,
	 * after enter bootloader, the response data is two bytes of 0x00 0x00.
	 */
	resp_len = sizeof(resp_data);
	memset(resp_data, 0, resp_len);
	error = cyapa_i2c_pip_cmd_irq_sync(cyapa,
			cmd, sizeof(cmd),
			resp_data, &resp_len,
			5000, cyapa_sort_pip_application_launch_data,
			true);
	if (error || resp_data[0] != 0x00 || resp_data[1] != 0x00)
		return error < 0 ? error : -EAGAIN;

	cyapa->operational = false;
	if (cyapa->gen == CYAPA_GEN5)
		cyapa->state = CYAPA_STATE_GEN5_BL;
	else if (cyapa->gen == CYAPA_GEN6)
		cyapa->state = CYAPA_STATE_GEN6_BL;
	return 0;
}