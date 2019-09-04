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
struct bnx2x {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BP_NOMCP (struct bnx2x*) ; 
 int /*<<< orphan*/  DRV_MSG_CODE_UNLOAD_DONE ; 
 int /*<<< orphan*/  DRV_MSG_CODE_UNLOAD_SKIP_LINK_RESET ; 
 int /*<<< orphan*/  bnx2x_fw_command (struct bnx2x*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void bnx2x_send_unload_done(struct bnx2x *bp, bool keep_link)
{
	u32 reset_param = keep_link ? DRV_MSG_CODE_UNLOAD_SKIP_LINK_RESET : 0;

	/* Report UNLOAD_DONE to MCP */
	if (!BP_NOMCP(bp))
		bnx2x_fw_command(bp, DRV_MSG_CODE_UNLOAD_DONE, reset_param);
}