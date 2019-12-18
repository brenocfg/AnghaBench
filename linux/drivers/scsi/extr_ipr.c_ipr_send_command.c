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
struct ipr_ioadl64_desc {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  ioarrin_reg; } ;
struct ipr_ioa_cfg {TYPE_1__ regs; scalar_t__ sis64; } ;
struct ipr_cmnd {int dma_addr; int dma_use_sg; struct ipr_ioa_cfg* ioa_cfg; } ;
typedef  int dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writeq (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ipr_send_command(struct ipr_cmnd *ipr_cmd)
{
	struct ipr_ioa_cfg *ioa_cfg = ipr_cmd->ioa_cfg;
	dma_addr_t send_dma_addr = ipr_cmd->dma_addr;

	if (ioa_cfg->sis64) {
		/* The default size is 256 bytes */
		send_dma_addr |= 0x1;

		/* If the number of ioadls * size of ioadl > 128 bytes,
		   then use a 512 byte ioarcb */
		if (ipr_cmd->dma_use_sg * sizeof(struct ipr_ioadl64_desc) > 128 )
			send_dma_addr |= 0x4;
		writeq(send_dma_addr, ioa_cfg->regs.ioarrin_reg);
	} else
		writel(send_dma_addr, ioa_cfg->regs.ioarrin_reg);
}