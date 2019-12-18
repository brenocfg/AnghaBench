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
typedef  int u16 ;
struct msg_anybus_init {int /*<<< orphan*/  op_mode; int /*<<< orphan*/  wd_val; int /*<<< orphan*/  notif_config; int /*<<< orphan*/  output_total_len; int /*<<< orphan*/  output_dpram_len; int /*<<< orphan*/  output_io_len; int /*<<< orphan*/  input_total_len; int /*<<< orphan*/  input_dpram_len; int /*<<< orphan*/  input_io_len; } ;
struct anybuss_memcfg {int input_io; int input_dpram; int input_total; int output_io; int output_dpram; int output_total; int offl_mode; } ;
struct anybuss_host {int dummy; } ;
struct anybuss_client {struct anybuss_host* host; } ;
typedef  int /*<<< orphan*/  msg ;

/* Variables and functions */
#define  AB_OFFL_MODE_CLEAR 130 
#define  AB_OFFL_MODE_FREEZE 129 
#define  AB_OFFL_MODE_SET 128 
 int /*<<< orphan*/  CMD_ANYBUS_INIT ; 
 int /*<<< orphan*/  CMD_START_INIT ; 
 int EINVAL ; 
 int OP_MODE_CD ; 
 int OP_MODE_FBFC ; 
 int OP_MODE_FBS ; 
 int _anybus_mbox_cmd (struct anybuss_host*,int /*<<< orphan*/ ,int,struct msg_anybus_init*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be16 (int) ; 

int anybuss_start_init(struct anybuss_client *client,
		       const struct anybuss_memcfg *cfg)
{
	int ret;
	u16 op_mode;
	struct anybuss_host *cd = client->host;
	struct msg_anybus_init msg = {
		.input_io_len = cpu_to_be16(cfg->input_io),
		.input_dpram_len = cpu_to_be16(cfg->input_dpram),
		.input_total_len = cpu_to_be16(cfg->input_total),
		.output_io_len = cpu_to_be16(cfg->output_io),
		.output_dpram_len = cpu_to_be16(cfg->output_dpram),
		.output_total_len = cpu_to_be16(cfg->output_total),
		.notif_config = cpu_to_be16(0x000F),
		.wd_val = cpu_to_be16(0),
	};

	switch (cfg->offl_mode) {
	case AB_OFFL_MODE_CLEAR:
		op_mode = 0;
		break;
	case AB_OFFL_MODE_FREEZE:
		op_mode = OP_MODE_FBFC;
		break;
	case AB_OFFL_MODE_SET:
		op_mode = OP_MODE_FBS;
		break;
	default:
		return -EINVAL;
	}
	msg.op_mode = cpu_to_be16(op_mode | OP_MODE_CD);
	ret = _anybus_mbox_cmd(cd, CMD_START_INIT, false, NULL, 0,
			       NULL, 0, NULL, 0);
	if (ret)
		return ret;
	return _anybus_mbox_cmd(cd, CMD_ANYBUS_INIT, false,
			&msg, sizeof(msg), NULL, 0, NULL, 0);
}