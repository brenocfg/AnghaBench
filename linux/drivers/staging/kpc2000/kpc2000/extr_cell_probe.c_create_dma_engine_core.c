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
struct resource {size_t start; int end; int /*<<< orphan*/  flags; } ;
struct mfd_cell {int id; int num_resources; struct resource* resources; int /*<<< orphan*/  name; scalar_t__ pdata_size; int /*<<< orphan*/ * platform_data; } ;
struct kp2000_device {int card_num; int /*<<< orphan*/  dma_base_resource; } ;
typedef  int /*<<< orphan*/  resources ;

/* Variables and functions */
 int /*<<< orphan*/  IORESOURCE_IRQ ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int KPC_DMA_ENGINE_SIZE ; 
 int /*<<< orphan*/  KP_DRIVER_NAME_DMA_CONTROLLER ; 
 int /*<<< orphan*/  PCARD_TO_DEV (struct kp2000_device*) ; 
 int /*<<< orphan*/  memset (struct resource**,int /*<<< orphan*/ ,int) ; 
 int mfd_add_devices (int /*<<< orphan*/ ,int,struct mfd_cell*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int  create_dma_engine_core(struct kp2000_device *pcard, size_t engine_regs_offset, int engine_num, int irq_num)
{
	struct mfd_cell  cell = { .id = engine_num };
	struct resource  resources[2];

	cell.platform_data = NULL;
	cell.pdata_size = 0;
	cell.name = KP_DRIVER_NAME_DMA_CONTROLLER;
	cell.num_resources = 2;

	memset(&resources, 0, sizeof(resources));

	resources[0].start = engine_regs_offset;
	resources[0].end   = engine_regs_offset + (KPC_DMA_ENGINE_SIZE - 1);
	resources[0].flags = IORESOURCE_MEM;

	resources[1].start = irq_num;
	resources[1].end   = irq_num;
	resources[1].flags = IORESOURCE_IRQ;

	cell.resources = resources;

	return mfd_add_devices(PCARD_TO_DEV(pcard),    // parent
			       pcard->card_num * 100,  // id
			       &cell,                  // struct mfd_cell *
			       1,                      // ndevs
			       &pcard->dma_base_resource,
			       0,                      // irq_base
			       NULL);                  // struct irq_domain *
}