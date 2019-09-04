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
struct bcm2835_smi_instance {int dummy; } ;
typedef  enum dma_transfer_direction { ____Placeholder_dma_transfer_direction } dma_transfer_direction ;

/* Variables and functions */
 int DMA_DEV_TO_MEM ; 
 int /*<<< orphan*/  SMICS ; 
 int SMICS_ACTIVE ; 
 int SMICS_ENABLE ; 
 int SMICS_WRITE ; 
 int read_smi_reg (struct bcm2835_smi_instance*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_smi_reg (struct bcm2835_smi_instance*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void smi_disable(struct bcm2835_smi_instance *inst,
	enum dma_transfer_direction direction)
{
	int smics_temp = read_smi_reg(inst, SMICS) & ~SMICS_ENABLE;

	if (direction == DMA_DEV_TO_MEM)
		smics_temp &= ~SMICS_WRITE;
	else
		smics_temp |= SMICS_WRITE;
	write_smi_reg(inst, smics_temp, SMICS);
	while (read_smi_reg(inst, SMICS) & SMICS_ACTIVE)
		;
}