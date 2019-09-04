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
typedef  int /*<<< orphan*/  u16 ;
struct mc_cmd_header {int /*<<< orphan*/  cmd_id; } ;
struct fsl_mc_command {int /*<<< orphan*/  header; } ;

/* Variables and functions */
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u16 mc_cmd_hdr_read_cmdid(struct fsl_mc_command *cmd)
{
	struct mc_cmd_header *hdr = (struct mc_cmd_header *)&cmd->header;
	u16 cmd_id = le16_to_cpu(hdr->cmd_id);

	return cmd_id;
}