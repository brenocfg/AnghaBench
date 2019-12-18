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
typedef  int /*<<< orphan*/  u16 ;
struct il_sensitivity_data {int dummy; } ;
struct il_sensitivity_cmd {int /*<<< orphan*/ * table; int /*<<< orphan*/  control; } ;
struct il_priv {int /*<<< orphan*/ * sensitivity_tbl; struct il_sensitivity_data sensitivity_data; } ;
struct il_host_cmd {int len; struct il_sensitivity_cmd* data; int /*<<< orphan*/  flags; int /*<<< orphan*/  id; } ;
typedef  int /*<<< orphan*/  cmd ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_ASYNC ; 
 int /*<<< orphan*/  C_SENSITIVITY ; 
 int /*<<< orphan*/  C_SENSITIVITY_CONTROL_WORK_TBL ; 
 int /*<<< orphan*/  D_CALIB (char*) ; 
 int HD_TBL_SIZE ; 
 int /*<<< orphan*/  il4965_prepare_legacy_sensitivity_tbl (struct il_priv*,struct il_sensitivity_data*,int /*<<< orphan*/ *) ; 
 int il_send_cmd (struct il_priv*,struct il_host_cmd*) ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (struct il_sensitivity_cmd*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
il4965_sensitivity_write(struct il_priv *il)
{
	struct il_sensitivity_cmd cmd;
	struct il_sensitivity_data *data = NULL;
	struct il_host_cmd cmd_out = {
		.id = C_SENSITIVITY,
		.len = sizeof(struct il_sensitivity_cmd),
		.flags = CMD_ASYNC,
		.data = &cmd,
	};

	data = &(il->sensitivity_data);

	memset(&cmd, 0, sizeof(cmd));

	il4965_prepare_legacy_sensitivity_tbl(il, data, &cmd.table[0]);

	/* Update uCode's "work" table, and copy it to DSP */
	cmd.control = C_SENSITIVITY_CONTROL_WORK_TBL;

	/* Don't send command to uCode if nothing has changed */
	if (!memcmp
	    (&cmd.table[0], &(il->sensitivity_tbl[0]),
	     sizeof(u16) * HD_TBL_SIZE)) {
		D_CALIB("No change in C_SENSITIVITY\n");
		return 0;
	}

	/* Copy table for comparison next time */
	memcpy(&(il->sensitivity_tbl[0]), &(cmd.table[0]),
	       sizeof(u16) * HD_TBL_SIZE);

	return il_send_cmd(il, &cmd_out);
}