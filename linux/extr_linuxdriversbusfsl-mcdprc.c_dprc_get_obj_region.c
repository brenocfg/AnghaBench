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
struct dprc_rsp_get_obj_region {int /*<<< orphan*/  size; int /*<<< orphan*/  base_addr; } ;
struct dprc_region_desc {int /*<<< orphan*/  size; int /*<<< orphan*/  base_offset; } ;
struct dprc_cmd_get_obj_region {char* obj_type; int /*<<< orphan*/  region_index; int /*<<< orphan*/  obj_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRC_CMDID_GET_OBJ_REG ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mc_encode_cmd_header (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mc_send_command (struct fsl_mc_io*,struct fsl_mc_command*) ; 
 int /*<<< orphan*/  strncpy (char*,char*,int) ; 

int dprc_get_obj_region(struct fsl_mc_io *mc_io,
			u32 cmd_flags,
			u16 token,
			char *obj_type,
			int obj_id,
			u8 region_index,
			struct dprc_region_desc *region_desc)
{
	struct fsl_mc_command cmd = { 0 };
	struct dprc_cmd_get_obj_region *cmd_params;
	struct dprc_rsp_get_obj_region *rsp_params;
	int err;

	/* prepare command */
	cmd.header = mc_encode_cmd_header(DPRC_CMDID_GET_OBJ_REG,
					  cmd_flags, token);
	cmd_params = (struct dprc_cmd_get_obj_region *)cmd.params;
	cmd_params->obj_id = cpu_to_le32(obj_id);
	cmd_params->region_index = region_index;
	strncpy(cmd_params->obj_type, obj_type, 16);
	cmd_params->obj_type[15] = '\0';

	/* send command to mc*/
	err = mc_send_command(mc_io, &cmd);
	if (err)
		return err;

	/* retrieve response parameters */
	rsp_params = (struct dprc_rsp_get_obj_region *)cmd.params;
	region_desc->base_offset = le64_to_cpu(rsp_params->base_addr);
	region_desc->size = le32_to_cpu(rsp_params->size);

	return 0;
}