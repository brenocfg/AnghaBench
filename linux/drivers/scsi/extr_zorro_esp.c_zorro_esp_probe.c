#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct zorro_esp_priv {int zorro3; int ctrl_data; void* board_base; struct esp* esp; } ;
struct zorro_driver_data {unsigned long offset; unsigned long dma_offset; scalar_t__ scsi_option; int /*<<< orphan*/  esp_ops; int /*<<< orphan*/  name; scalar_t__ absolute; } ;
struct zorro_device_id {size_t driver_data; } ;
struct TYPE_6__ {int /*<<< orphan*/  coherent_dma_mask; } ;
struct TYPE_5__ {int er_Type; } ;
struct zorro_dev {TYPE_2__ dev; TYPE_1__ rom; } ;
struct scsi_host_template {int dummy; } ;
struct fastlane_dma_registers {int dummy; } ;
struct esp {int scsi_id; int scsi_id_mask; int cfreq; void* regs; void* dma_regs; int /*<<< orphan*/  command_block_dma; int /*<<< orphan*/  command_block; TYPE_2__* dev; void* fifo_reg; int /*<<< orphan*/  ops; struct Scsi_Host* host; } ;
struct Scsi_Host {unsigned long base; int this_id; int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIT_MASK (int) ; 
 int EBUSY ; 
 int ENODEV ; 
 int ENOMEM ; 
 int ERT_TYPEMASK ; 
 int ERT_ZORROIII ; 
 int /*<<< orphan*/  ESP_CFG1 ; 
 int ESP_CONFIG1_PENABLE ; 
 int ESP_FDATA ; 
 int FASTLANE_DMA_EDI ; 
 int FASTLANE_DMA_ESI ; 
 int FASTLANE_DMA_FCODE ; 
 int FASTLANE_ESP_ADDR ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 int /*<<< orphan*/  IRQ_AMIGA_PORTS ; 
 size_t ZORRO_BLZ1230II ; 
 size_t ZORRO_FASTLANE ; 
 void* ZTWO_VADDR (unsigned long) ; 
 int /*<<< orphan*/  dev_set_drvdata (TYPE_2__*,struct zorro_esp_priv*) ; 
 int /*<<< orphan*/  dma_alloc_coherent (TYPE_2__*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_coherent (TYPE_2__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct esp*) ; 
 void* ioremap_nocache (unsigned long,int) ; 
 int /*<<< orphan*/  iounmap (void*) ; 
 int /*<<< orphan*/  kfree (struct zorro_esp_priv*) ; 
 struct zorro_esp_priv* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ,unsigned long) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct esp*) ; 
 int /*<<< orphan*/  scsi_esp_intr ; 
 int scsi_esp_register (struct esp*) ; 
 struct scsi_host_template scsi_esp_template ; 
 struct Scsi_Host* scsi_host_alloc (struct scsi_host_template*,int) ; 
 int /*<<< orphan*/  scsi_host_put (struct Scsi_Host*) ; 
 struct esp* shost_priv (struct Scsi_Host*) ; 
 struct zorro_driver_data* zorro_esp_boards ; 
 int zorro_esp_read8 (struct esp*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zorro_esp_write8 (struct esp*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zorro_release_device (struct zorro_dev*) ; 
 int /*<<< orphan*/  zorro_request_device (struct zorro_dev*,int /*<<< orphan*/ ) ; 
 unsigned long zorro_resource_start (struct zorro_dev*) ; 

__attribute__((used)) static int zorro_esp_probe(struct zorro_dev *z,
				       const struct zorro_device_id *ent)
{
	struct scsi_host_template *tpnt = &scsi_esp_template;
	struct Scsi_Host *host;
	struct esp *esp;
	const struct zorro_driver_data *zdd;
	struct zorro_esp_priv *zep;
	unsigned long board, ioaddr, dmaaddr;
	int err;

	board = zorro_resource_start(z);
	zdd = &zorro_esp_boards[ent->driver_data];

	pr_info("%s found at address 0x%lx.\n", zdd->name, board);

	zep = kzalloc(sizeof(*zep), GFP_KERNEL);
	if (!zep) {
		pr_err("Can't allocate device private data!\n");
		return -ENOMEM;
	}

	/* let's figure out whether we have a Zorro II or Zorro III board */
	if ((z->rom.er_Type & ERT_TYPEMASK) == ERT_ZORROIII) {
		if (board > 0xffffff)
			zep->zorro3 = 1;
	} else {
		/*
		 * Even though most of these boards identify as Zorro II,
		 * they are in fact CPU expansion slot boards and have full
		 * access to all of memory. Fix up DMA bitmask here.
		 */
		z->dev.coherent_dma_mask = DMA_BIT_MASK(32);
	}

	/*
	 * If Zorro III and ID matches Fastlane, our device table entry
	 * contains data for the Blizzard 1230 II board which does share the
	 * same ID. Fix up device table entry here.
	 * TODO: Some Cyberstom060 boards also share this ID but would need
	 * to use the Cyberstorm I driver data ... we catch this by checking
	 * for presence of ESP chip later, but don't try to fix up yet.
	 */
	if (zep->zorro3 && ent->driver_data == ZORRO_BLZ1230II) {
		pr_info("%s at address 0x%lx is Fastlane Z3, fixing data!\n",
			zdd->name, board);
		zdd = &zorro_esp_boards[ZORRO_FASTLANE];
	}

	if (zdd->absolute) {
		ioaddr  = zdd->offset;
		dmaaddr = zdd->dma_offset;
	} else {
		ioaddr  = board + zdd->offset;
		dmaaddr = board + zdd->dma_offset;
	}

	if (!zorro_request_device(z, zdd->name)) {
		pr_err("cannot reserve region 0x%lx, abort\n",
		       board);
		err = -EBUSY;
		goto fail_free_zep;
	}

	host = scsi_host_alloc(tpnt, sizeof(struct esp));

	if (!host) {
		pr_err("No host detected; board configuration problem?\n");
		err = -ENOMEM;
		goto fail_release_device;
	}

	host->base		= ioaddr;
	host->this_id		= 7;

	esp			= shost_priv(host);
	esp->host		= host;
	esp->dev		= &z->dev;

	esp->scsi_id		= host->this_id;
	esp->scsi_id_mask	= (1 << esp->scsi_id);

	esp->cfreq = 40000000;

	zep->esp = esp;

	dev_set_drvdata(esp->dev, zep);

	/* additional setup required for Fastlane */
	if (zep->zorro3 && ent->driver_data == ZORRO_BLZ1230II) {
		/* map full address space up to ESP base for DMA */
		zep->board_base = ioremap_nocache(board,
						FASTLANE_ESP_ADDR-1);
		if (!zep->board_base) {
			pr_err("Cannot allocate board address space\n");
			err = -ENOMEM;
			goto fail_free_host;
		}
		/* initialize DMA control shadow register */
		zep->ctrl_data = (FASTLANE_DMA_FCODE |
				  FASTLANE_DMA_EDI | FASTLANE_DMA_ESI);
	}

	esp->ops = zdd->esp_ops;

	if (ioaddr > 0xffffff)
		esp->regs = ioremap_nocache(ioaddr, 0x20);
	else
		/* ZorroII address space remapped nocache by early startup */
		esp->regs = ZTWO_VADDR(ioaddr);

	if (!esp->regs) {
		err = -ENOMEM;
		goto fail_unmap_fastlane;
	}

	esp->fifo_reg = esp->regs + ESP_FDATA * 4;

	/* Check whether a Blizzard 12x0 or CyberstormII really has SCSI */
	if (zdd->scsi_option) {
		zorro_esp_write8(esp, (ESP_CONFIG1_PENABLE | 7), ESP_CFG1);
		if (zorro_esp_read8(esp, ESP_CFG1) != (ESP_CONFIG1_PENABLE|7)) {
			err = -ENODEV;
			goto fail_unmap_regs;
		}
	}

	if (zep->zorro3) {
		/*
		 * Only Fastlane Z3 for now - add switch for correct struct
		 * dma_registers size if adding any more
		 */
		esp->dma_regs = ioremap_nocache(dmaaddr,
				sizeof(struct fastlane_dma_registers));
	} else
		/* ZorroII address space remapped nocache by early startup */
		esp->dma_regs = ZTWO_VADDR(dmaaddr);

	if (!esp->dma_regs) {
		err = -ENOMEM;
		goto fail_unmap_regs;
	}

	esp->command_block = dma_alloc_coherent(esp->dev, 16,
						&esp->command_block_dma,
						GFP_KERNEL);

	if (!esp->command_block) {
		err = -ENOMEM;
		goto fail_unmap_dma_regs;
	}

	host->irq = IRQ_AMIGA_PORTS;
	err = request_irq(host->irq, scsi_esp_intr, IRQF_SHARED,
			  "Amiga Zorro ESP", esp);
	if (err < 0) {
		err = -ENODEV;
		goto fail_free_command_block;
	}

	/* register the chip */
	err = scsi_esp_register(esp);

	if (err) {
		err = -ENOMEM;
		goto fail_free_irq;
	}

	return 0;

fail_free_irq:
	free_irq(host->irq, esp);

fail_free_command_block:
	dma_free_coherent(esp->dev, 16,
			  esp->command_block,
			  esp->command_block_dma);

fail_unmap_dma_regs:
	if (zep->zorro3)
		iounmap(esp->dma_regs);

fail_unmap_regs:
	if (ioaddr > 0xffffff)
		iounmap(esp->regs);

fail_unmap_fastlane:
	if (zep->zorro3)
		iounmap(zep->board_base);

fail_free_host:
	scsi_host_put(host);

fail_release_device:
	zorro_release_device(z);

fail_free_zep:
	kfree(zep);

	return err;
}