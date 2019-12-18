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
struct sti_hqvdp_cmd {int dummy; } ;
struct sti_hqvdp {int hqvdp_cmd_paddr; scalar_t__ regs; } ;
typedef  int dma_addr_t ;

/* Variables and functions */
 scalar_t__ HQVDP_MBX_NEXT_CMD ; 
 unsigned int NB_VDP_CMD ; 
 int readl (scalar_t__) ; 

__attribute__((used)) static int sti_hqvdp_get_next_cmd(struct sti_hqvdp *hqvdp)
{
	int next_cmd;
	dma_addr_t cmd = hqvdp->hqvdp_cmd_paddr;
	unsigned int i;

	next_cmd = readl(hqvdp->regs + HQVDP_MBX_NEXT_CMD);

	for (i = 0; i < NB_VDP_CMD; i++) {
		if (cmd == next_cmd)
			return i * sizeof(struct sti_hqvdp_cmd);

		cmd += sizeof(struct sti_hqvdp_cmd);
	}

	return -1;
}