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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct fsl_mc_io {int dummy; } ;
struct fsl_mc_command {scalar_t__ params; int /*<<< orphan*/  header; int /*<<< orphan*/  member_0; } ;
struct dprc_irq_cfg {int val; int irq_num; int /*<<< orphan*/  paddr; } ;
struct dprc_cmd_set_obj_irq {char* obj_type; void* obj_id; void* irq_num; int /*<<< orphan*/  irq_addr; int /*<<< orphan*/  irq_index; void* irq_val; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRC_CMDID_SET_OBJ_IRQ ; 
 void* cpu_to_le32 (int) ; 
 int /*<<< orphan*/  cpu_to_le64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mc_encode_cmd_header (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mc_send_command (struct fsl_mc_io*,struct fsl_mc_command*) ; 
 int /*<<< orphan*/  strncpy (char*,char*,int) ; 

int dprc_set_obj_irq(struct fsl_mc_io *mc_io,
		     u32 cmd_flags,
		     u16 token,
		     char *obj_type,
		     int obj_id,
		     u8 irq_index,
		     struct dprc_irq_cfg *irq_cfg)
{
	struct fsl_mc_command cmd = { 0 };
	struct dprc_cmd_set_obj_irq *cmd_params;

	/* prepare command */
	cmd.header = mc_encode_cmd_header(DPRC_CMDID_SET_OBJ_IRQ,
					  cmd_flags,
					  token);
	cmd_params = (struct dprc_cmd_set_obj_irq *)cmd.params;
	cmd_params->irq_val = cpu_to_le32(irq_cfg->val);
	cmd_params->irq_index = irq_index;
	cmd_params->irq_addr = cpu_to_le64(irq_cfg->paddr);
	cmd_params->irq_num = cpu_to_le32(irq_cfg->irq_num);
	cmd_params->obj_id = cpu_to_le32(obj_id);
	strncpy(cmd_params->obj_type, obj_type, 16);
	cmd_params->obj_type[15] = '\0';

	/* send command to mc*/
	return mc_send_command(mc_io, &cmd);
}