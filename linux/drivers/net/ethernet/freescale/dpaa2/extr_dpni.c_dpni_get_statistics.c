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
struct TYPE_2__ {int /*<<< orphan*/ * counter; } ;
union dpni_statistics {TYPE_1__ raw; } ;
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct fsl_mc_io {int dummy; } ;
struct fsl_mc_command {scalar_t__ params; int /*<<< orphan*/  header; int /*<<< orphan*/  member_0; } ;
struct dpni_rsp_get_statistics {int /*<<< orphan*/ * counter; } ;
struct dpni_cmd_get_statistics {int /*<<< orphan*/  page_number; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPNI_CMDID_GET_STATISTICS ; 
 int DPNI_STATISTICS_CNT ; 
 int /*<<< orphan*/  le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mc_encode_cmd_header (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mc_send_command (struct fsl_mc_io*,struct fsl_mc_command*) ; 

int dpni_get_statistics(struct fsl_mc_io *mc_io,
			u32 cmd_flags,
			u16 token,
			u8 page,
			union dpni_statistics *stat)
{
	struct fsl_mc_command cmd = { 0 };
	struct dpni_cmd_get_statistics *cmd_params;
	struct dpni_rsp_get_statistics *rsp_params;
	int i, err;

	/* prepare command */
	cmd.header = mc_encode_cmd_header(DPNI_CMDID_GET_STATISTICS,
					  cmd_flags,
					  token);
	cmd_params = (struct dpni_cmd_get_statistics *)cmd.params;
	cmd_params->page_number = page;

	/* send command to mc */
	err = mc_send_command(mc_io, &cmd);
	if (err)
		return err;

	/* retrieve response parameters */
	rsp_params = (struct dpni_rsp_get_statistics *)cmd.params;
	for (i = 0; i < DPNI_STATISTICS_CNT; i++)
		stat->raw.counter[i] = le64_to_cpu(rsp_params->counter[i]);

	return 0;
}