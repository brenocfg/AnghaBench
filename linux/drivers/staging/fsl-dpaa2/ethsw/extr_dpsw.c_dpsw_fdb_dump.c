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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct fsl_mc_io {int dummy; } ;
struct fsl_mc_command {scalar_t__ params; int /*<<< orphan*/  header; int /*<<< orphan*/  member_0; } ;
struct dpsw_rsp_fdb_dump {int /*<<< orphan*/  num_entries; } ;
struct dpsw_cmd_fdb_dump {int /*<<< orphan*/  iova_size; int /*<<< orphan*/  iova_addr; int /*<<< orphan*/  fdb_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPSW_CMDID_FDB_DUMP ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mc_encode_cmd_header (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mc_send_command (struct fsl_mc_io*,struct fsl_mc_command*) ; 

int dpsw_fdb_dump(struct fsl_mc_io *mc_io,
		  u32 cmd_flags,
		  u16 token,
		  u16 fdb_id,
		  u64 iova_addr,
		  u32 iova_size,
		  u16 *num_entries)
{
	struct dpsw_cmd_fdb_dump *cmd_params;
	struct dpsw_rsp_fdb_dump *rsp_params;
	struct fsl_mc_command cmd = { 0 };
	int err;

	/* prepare command */
	cmd.header = mc_encode_cmd_header(DPSW_CMDID_FDB_DUMP,
					  cmd_flags,
					  token);
	cmd_params = (struct dpsw_cmd_fdb_dump *)cmd.params;
	cmd_params->fdb_id = cpu_to_le16(fdb_id);
	cmd_params->iova_addr = cpu_to_le64(iova_addr);
	cmd_params->iova_size = cpu_to_le32(iova_size);

	/* send command to mc */
	err = mc_send_command(mc_io, &cmd);
	if (err)
		return err;

	rsp_params = (struct dpsw_rsp_fdb_dump *)cmd.params;
	*num_entries = le16_to_cpu(rsp_params->num_entries);

	return 0;
}