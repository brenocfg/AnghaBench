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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct fsl_mc_io {int dummy; } ;
struct fsl_mc_command {scalar_t__ params; int /*<<< orphan*/  header; int /*<<< orphan*/  member_0; } ;
struct dpni_link_cfg {int /*<<< orphan*/  options; int /*<<< orphan*/  rate; } ;
struct dpni_cmd_link_cfg {int /*<<< orphan*/  options; int /*<<< orphan*/  rate; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPNI_CMDID_GET_LINK_CFG ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mc_encode_cmd_header (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mc_send_command (struct fsl_mc_io*,struct fsl_mc_command*) ; 

int dpni_get_link_cfg(struct fsl_mc_io *mc_io,
		      u32 cmd_flags,
		      u16 token,
		      struct dpni_link_cfg *cfg)
{
	struct fsl_mc_command cmd = { 0 };
	struct dpni_cmd_link_cfg *rsp_params;
	int err;

	/* prepare command */
	cmd.header = mc_encode_cmd_header(DPNI_CMDID_GET_LINK_CFG,
					  cmd_flags,
					  token);

	/* send command to mc*/
	err = mc_send_command(mc_io, &cmd);
	if (err)
		return err;

	/* retrieve response parameters */
	rsp_params = (struct dpni_cmd_link_cfg *)cmd.params;
	cfg->rate = le32_to_cpu(rsp_params->rate);
	cfg->options = le64_to_cpu(rsp_params->options);

	return err;
}