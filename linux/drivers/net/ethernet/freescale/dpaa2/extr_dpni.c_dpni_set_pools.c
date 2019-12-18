#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct fsl_mc_io {int dummy; } ;
struct fsl_mc_command {scalar_t__ params; int /*<<< orphan*/  header; int /*<<< orphan*/  member_0; } ;
struct dpni_pools_cfg {TYPE_1__* pools; int /*<<< orphan*/  num_dpbp; } ;
struct dpni_cmd_set_pools {int /*<<< orphan*/  backup_pool_mask; int /*<<< orphan*/ * buffer_size; int /*<<< orphan*/ * dpbp_id; int /*<<< orphan*/  num_dpbp; } ;
struct TYPE_2__ {int /*<<< orphan*/  backup_pool; int /*<<< orphan*/  buffer_size; int /*<<< orphan*/  dpbp_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPNI_BACKUP_POOL (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DPNI_CMDID_SET_POOLS ; 
 int DPNI_MAX_DPBP ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mc_encode_cmd_header (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mc_send_command (struct fsl_mc_io*,struct fsl_mc_command*) ; 

int dpni_set_pools(struct fsl_mc_io *mc_io,
		   u32 cmd_flags,
		   u16 token,
		   const struct dpni_pools_cfg *cfg)
{
	struct fsl_mc_command cmd = { 0 };
	struct dpni_cmd_set_pools *cmd_params;
	int i;

	/* prepare command */
	cmd.header = mc_encode_cmd_header(DPNI_CMDID_SET_POOLS,
					  cmd_flags,
					  token);
	cmd_params = (struct dpni_cmd_set_pools *)cmd.params;
	cmd_params->num_dpbp = cfg->num_dpbp;
	for (i = 0; i < DPNI_MAX_DPBP; i++) {
		cmd_params->dpbp_id[i] = cpu_to_le32(cfg->pools[i].dpbp_id);
		cmd_params->buffer_size[i] =
			cpu_to_le16(cfg->pools[i].buffer_size);
		cmd_params->backup_pool_mask |=
			DPNI_BACKUP_POOL(cfg->pools[i].backup_pool, i);
	}

	/* send command to mc*/
	return mc_send_command(mc_io, &cmd);
}