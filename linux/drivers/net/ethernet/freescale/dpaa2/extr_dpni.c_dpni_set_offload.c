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
struct dpni_cmd_set_offload {int dpni_offload; int /*<<< orphan*/  config; } ;
typedef  enum dpni_offload { ____Placeholder_dpni_offload } dpni_offload ;

/* Variables and functions */
 int /*<<< orphan*/  DPNI_CMDID_SET_OFFLOAD ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mc_encode_cmd_header (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mc_send_command (struct fsl_mc_io*,struct fsl_mc_command*) ; 

int dpni_set_offload(struct fsl_mc_io *mc_io,
		     u32 cmd_flags,
		     u16 token,
		     enum dpni_offload type,
		     u32 config)
{
	struct fsl_mc_command cmd = { 0 };
	struct dpni_cmd_set_offload *cmd_params;

	cmd.header = mc_encode_cmd_header(DPNI_CMDID_SET_OFFLOAD,
					  cmd_flags,
					  token);
	cmd_params = (struct dpni_cmd_set_offload *)cmd.params;
	cmd_params->dpni_offload = type;
	cmd_params->config = cpu_to_le32(config);

	return mc_send_command(mc_io, &cmd);
}