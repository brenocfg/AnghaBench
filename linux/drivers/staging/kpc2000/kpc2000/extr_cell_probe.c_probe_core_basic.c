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
struct resource {int start; int end; int /*<<< orphan*/  flags; } ;
struct mfd_cell {unsigned int id; char* name; int pdata_size; int num_resources; struct resource* resources; struct kpc_core_device_platdata* platform_data; } ;
struct kpc_core_device_platdata {int /*<<< orphan*/  ddna; int /*<<< orphan*/  ssid; int /*<<< orphan*/  hardware_revision; int /*<<< orphan*/  build_version; int /*<<< orphan*/  card_id; } ;
struct kp2000_device {int card_num; int /*<<< orphan*/  regs_base_resource; TYPE_1__* pdev; int /*<<< orphan*/  ddna; int /*<<< orphan*/  ssid; int /*<<< orphan*/  hardware_revision; int /*<<< orphan*/  build_version; int /*<<< orphan*/  card_id; } ;
struct core_table_entry {int offset; int length; int /*<<< orphan*/  type; } ;
typedef  int /*<<< orphan*/  resources ;
struct TYPE_2__ {int irq; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  IORESOURCE_IRQ ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  KPC_OLD_C2S_DMA_CH_NUM (struct core_table_entry const) ; 
 int /*<<< orphan*/  KPC_OLD_S2C_DMA_CH_NUM (struct core_table_entry const) ; 
 int /*<<< orphan*/  PCARD_TO_DEV (struct kp2000_device*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  memset (struct resource**,int /*<<< orphan*/ ,int) ; 
 int mfd_add_devices (int /*<<< orphan*/ ,int,struct mfd_cell*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int probe_core_basic(unsigned int core_num, struct kp2000_device *pcard,
			    char *name, const struct core_table_entry cte)
{
	struct mfd_cell  cell = { .id = core_num, .name = name };
	struct resource resources[2];

	struct kpc_core_device_platdata core_pdata = {
		.card_id           = pcard->card_id,
		.build_version     = pcard->build_version,
		.hardware_revision = pcard->hardware_revision,
		.ssid              = pcard->ssid,
		.ddna              = pcard->ddna,
	};

	dev_dbg(&pcard->pdev->dev, "Found Basic core: type = %02d  dma = %02x / %02x  offset = 0x%x  length = 0x%x (%d regs)\n", cte.type, KPC_OLD_S2C_DMA_CH_NUM(cte), KPC_OLD_C2S_DMA_CH_NUM(cte), cte.offset, cte.length, cte.length / 8);

	cell.platform_data = &core_pdata;
	cell.pdata_size = sizeof(struct kpc_core_device_platdata);
	cell.num_resources = 2;

	memset(&resources, 0, sizeof(resources));

	resources[0].start = cte.offset;
	resources[0].end   = cte.offset + (cte.length - 1);
	resources[0].flags = IORESOURCE_MEM;

	resources[1].start = pcard->pdev->irq;
	resources[1].end   = pcard->pdev->irq;
	resources[1].flags = IORESOURCE_IRQ;

	cell.resources = resources;

	return mfd_add_devices(PCARD_TO_DEV(pcard),    // parent
			       pcard->card_num * 100,  // id
			       &cell,                  // struct mfd_cell *
			       1,                      // ndevs
			       &pcard->regs_base_resource,
			       0,                      // irq_base
			       NULL);                  // struct irq_domain *
}