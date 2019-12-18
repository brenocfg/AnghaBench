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
struct dpsw_cmd_vlan_remove {int /*<<< orphan*/  vlan_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPSW_CMDID_VLAN_REMOVE ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mc_encode_cmd_header (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mc_send_command (struct fsl_mc_io*,struct fsl_mc_command*) ; 

int dpsw_vlan_remove(struct fsl_mc_io *mc_io,
		     u32 cmd_flags,
		     u16 token,
		     u16 vlan_id)
{
	struct fsl_mc_command cmd = { 0 };
	struct dpsw_cmd_vlan_remove *cmd_params;

	/* prepare command */
	cmd.header = mc_encode_cmd_header(DPSW_CMDID_VLAN_REMOVE,
					  cmd_flags,
					  token);
	cmd_params = (struct dpsw_cmd_vlan_remove *)cmd.params;
	cmd_params->vlan_id = cpu_to_le16(vlan_id);

	/* send command to mc*/
	return mc_send_command(mc_io, &cmd);
}