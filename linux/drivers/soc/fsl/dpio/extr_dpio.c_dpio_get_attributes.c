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
struct dpio_rsp_get_attr {int channel_mode; int /*<<< orphan*/  qbman_version; int /*<<< orphan*/  qbman_portal_ci_addr; int /*<<< orphan*/  qbman_portal_ce_addr; int /*<<< orphan*/  num_priorities; int /*<<< orphan*/  qbman_portal_id; int /*<<< orphan*/  id; } ;
struct dpio_attr {int channel_mode; void* qbman_version; void* qbman_portal_ci_offset; void* qbman_portal_ce_offset; int /*<<< orphan*/  num_priorities; int /*<<< orphan*/  qbman_portal_id; void* id; } ;

/* Variables and functions */
 int DPIO_CHANNEL_MODE_MASK ; 
 int /*<<< orphan*/  DPIO_CMDID_GET_ATTR ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 void* le32_to_cpu (int /*<<< orphan*/ ) ; 
 void* le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mc_encode_cmd_header (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mc_send_command (struct fsl_mc_io*,struct fsl_mc_command*) ; 

int dpio_get_attributes(struct fsl_mc_io *mc_io,
			u32 cmd_flags,
			u16 token,
			struct dpio_attr *attr)
{
	struct fsl_mc_command cmd = { 0 };
	struct dpio_rsp_get_attr *dpio_rsp;
	int err;

	/* prepare command */
	cmd.header = mc_encode_cmd_header(DPIO_CMDID_GET_ATTR,
					  cmd_flags,
					  token);

	err = mc_send_command(mc_io, &cmd);
	if (err)
		return err;

	/* retrieve response parameters */
	dpio_rsp = (struct dpio_rsp_get_attr *)cmd.params;
	attr->id = le32_to_cpu(dpio_rsp->id);
	attr->qbman_portal_id = le16_to_cpu(dpio_rsp->qbman_portal_id);
	attr->num_priorities = dpio_rsp->num_priorities;
	attr->channel_mode = dpio_rsp->channel_mode & DPIO_CHANNEL_MODE_MASK;
	attr->qbman_portal_ce_offset =
		le64_to_cpu(dpio_rsp->qbman_portal_ce_addr);
	attr->qbman_portal_ci_offset =
		le64_to_cpu(dpio_rsp->qbman_portal_ci_addr);
	attr->qbman_version = le32_to_cpu(dpio_rsp->qbman_version);

	return 0;
}