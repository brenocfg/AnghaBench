#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_3__ {int /*<<< orphan*/  buf_size; int /*<<< orphan*/  buf_phy_addr_hi; int /*<<< orphan*/  buf_phy_addr_lo; } ;
struct TYPE_4__ {TYPE_1__ cmd_setup_tmr; } ;
struct psp_gfx_cmd_resp {TYPE_2__ cmd; int /*<<< orphan*/  cmd_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFX_CMD_ID_SETUP_TMR ; 
 int /*<<< orphan*/  lower_32_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  upper_32_bits (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void psp_prep_tmr_cmd_buf(struct psp_gfx_cmd_resp *cmd,
				 uint64_t tmr_mc, uint32_t size)
{
	cmd->cmd_id = GFX_CMD_ID_SETUP_TMR;
	cmd->cmd.cmd_setup_tmr.buf_phy_addr_lo = lower_32_bits(tmr_mc);
	cmd->cmd.cmd_setup_tmr.buf_phy_addr_hi = upper_32_bits(tmr_mc);
	cmd->cmd.cmd_setup_tmr.buf_size = size;
}