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
struct dpsw_tci_cfg {int /*<<< orphan*/  pcp; int /*<<< orphan*/  dei; int /*<<< orphan*/  vlan_id; } ;
struct dpsw_cmd_if_set_tci {void* conf; void* if_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEI ; 
 int /*<<< orphan*/  DPSW_CMDID_IF_SET_TCI ; 
 int /*<<< orphan*/  PCP ; 
 int /*<<< orphan*/  VLAN_ID ; 
 void* cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dpsw_set_field (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mc_encode_cmd_header (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mc_send_command (struct fsl_mc_io*,struct fsl_mc_command*) ; 

int dpsw_if_set_tci(struct fsl_mc_io *mc_io,
		    u32 cmd_flags,
		    u16 token,
		    u16 if_id,
		    const struct dpsw_tci_cfg *cfg)
{
	struct fsl_mc_command cmd = { 0 };
	struct dpsw_cmd_if_set_tci *cmd_params;
	u16 tmp_conf = 0;

	/* prepare command */
	cmd.header = mc_encode_cmd_header(DPSW_CMDID_IF_SET_TCI,
					  cmd_flags,
					  token);
	cmd_params = (struct dpsw_cmd_if_set_tci *)cmd.params;
	cmd_params->if_id = cpu_to_le16(if_id);
	dpsw_set_field(tmp_conf, VLAN_ID, cfg->vlan_id);
	dpsw_set_field(tmp_conf, DEI, cfg->dei);
	dpsw_set_field(tmp_conf, PCP, cfg->pcp);
	cmd_params->conf = cpu_to_le16(tmp_conf);

	/* send command to mc*/
	return mc_send_command(mc_io, &cmd);
}