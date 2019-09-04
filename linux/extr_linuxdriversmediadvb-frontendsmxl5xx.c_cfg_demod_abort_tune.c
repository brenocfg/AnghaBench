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
struct mxl {int /*<<< orphan*/  demod; } ;
struct MXL_HYDRA_DEMOD_ABORT_TUNE_T {int /*<<< orphan*/  demod_id; } ;
typedef  int /*<<< orphan*/  abort_tune_cmd ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_HYDRA_CMD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct MXL_HYDRA_DEMOD_ABORT_TUNE_T*,int*) ; 
 int /*<<< orphan*/  MXL_CMD_WRITE ; 
 int /*<<< orphan*/  MXL_HYDRA_ABORT_TUNE_CMD ; 
 int MXL_HYDRA_CMD_HEADER_SIZE ; 
 int MXL_HYDRA_OEM_MAX_CMD_BUFF_LEN ; 
 int send_command (struct mxl*,int,int*) ; 

__attribute__((used)) static int cfg_demod_abort_tune(struct mxl *state)
{
	struct MXL_HYDRA_DEMOD_ABORT_TUNE_T abort_tune_cmd;
	u8 cmd_size = sizeof(abort_tune_cmd);
	u8 cmd_buff[MXL_HYDRA_OEM_MAX_CMD_BUFF_LEN];

	abort_tune_cmd.demod_id = state->demod;
	BUILD_HYDRA_CMD(MXL_HYDRA_ABORT_TUNE_CMD, MXL_CMD_WRITE,
			cmd_size, &abort_tune_cmd, cmd_buff);
	return send_command(state, cmd_size + MXL_HYDRA_CMD_HEADER_SIZE,
			    &cmd_buff[0]);
}