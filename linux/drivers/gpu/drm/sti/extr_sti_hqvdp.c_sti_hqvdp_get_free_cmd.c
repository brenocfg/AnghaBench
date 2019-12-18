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
typedef  scalar_t__ u32 ;
struct sti_hqvdp_cmd {int dummy; } ;
struct sti_hqvdp {scalar_t__ hqvdp_cmd_paddr; scalar_t__ regs; } ;

/* Variables and functions */
 scalar_t__ HQVDP_MBX_CURRENT_CMD ; 
 scalar_t__ HQVDP_MBX_NEXT_CMD ; 
 int NB_VDP_CMD ; 
 scalar_t__ readl (scalar_t__) ; 

__attribute__((used)) static int sti_hqvdp_get_free_cmd(struct sti_hqvdp *hqvdp)
{
	u32 curr_cmd, next_cmd;
	u32 cmd = hqvdp->hqvdp_cmd_paddr;
	int i;

	curr_cmd = readl(hqvdp->regs + HQVDP_MBX_CURRENT_CMD);
	next_cmd = readl(hqvdp->regs + HQVDP_MBX_NEXT_CMD);

	for (i = 0; i < NB_VDP_CMD; i++) {
		if ((cmd != curr_cmd) && (cmd != next_cmd))
			return i * sizeof(struct sti_hqvdp_cmd);
		cmd += sizeof(struct sti_hqvdp_cmd);
	}

	return -1;
}