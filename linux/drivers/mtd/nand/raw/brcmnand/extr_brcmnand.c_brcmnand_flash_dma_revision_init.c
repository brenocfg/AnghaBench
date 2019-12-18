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
struct brcmnand_controller {int nand_version; int /*<<< orphan*/  flash_dma_offsets; } ;

/* Variables and functions */
 int /*<<< orphan*/  flash_dma_regs_v1 ; 
 int /*<<< orphan*/  flash_dma_regs_v4 ; 

__attribute__((used)) static void brcmnand_flash_dma_revision_init(struct brcmnand_controller *ctrl)
{
	/* flash_dma register offsets */
	if (ctrl->nand_version >= 0x0703)
		ctrl->flash_dma_offsets = flash_dma_regs_v4;
	else
		ctrl->flash_dma_offsets = flash_dma_regs_v1;
}