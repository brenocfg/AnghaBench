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
struct wd719x_host_param {int dummy; } ;
struct wd719x {size_t type; int /*<<< orphan*/  params_phys; TYPE_2__* params; TYPE_1__* pdev; int /*<<< orphan*/  hash_phys; TYPE_2__* hash_virt; int /*<<< orphan*/ * fw_virt; struct Scsi_Host* sh; int /*<<< orphan*/  active_scbs; } ;
struct Scsi_Host {int this_id; int /*<<< orphan*/  irq; int /*<<< orphan*/  base; } ;
struct TYPE_4__ {int own_scsi_id; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 int WD719X_EE_SCSI_ID_MASK ; 
 int WD719X_HASH_TABLE_SIZE ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,char const* const,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,...) ; 
 void* dma_alloc_coherent (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct wd719x*) ; 
 int /*<<< orphan*/  pci_resource_start (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct wd719x*) ; 
 struct wd719x* shost_priv (struct Scsi_Host*) ; 
 int wd719x_chip_init (struct wd719x*) ; 
 size_t wd719x_detect_type (struct wd719x*) ; 
 int /*<<< orphan*/  wd719x_interrupt ; 
 int /*<<< orphan*/  wd719x_read_eeprom (struct wd719x*) ; 

__attribute__((used)) static int wd719x_board_found(struct Scsi_Host *sh)
{
	struct wd719x *wd = shost_priv(sh);
	static const char * const card_types[] = {
		"Unknown card", "WD7193", "WD7197", "WD7296"
	};
	int ret;

	INIT_LIST_HEAD(&wd->active_scbs);

	sh->base = pci_resource_start(wd->pdev, 0);

	wd->type = wd719x_detect_type(wd);

	wd->sh = sh;
	sh->irq = wd->pdev->irq;
	wd->fw_virt = NULL;

	/* memory area for host (EEPROM) parameters */
	wd->params = dma_alloc_coherent(&wd->pdev->dev,
					sizeof(struct wd719x_host_param),
					&wd->params_phys, GFP_KERNEL);
	if (!wd->params) {
		dev_warn(&wd->pdev->dev, "unable to allocate parameter buffer\n");
		return -ENOMEM;
	}

	/* memory area for the RISC for hash table of outstanding requests */
	wd->hash_virt = dma_alloc_coherent(&wd->pdev->dev,
					   WD719X_HASH_TABLE_SIZE,
					   &wd->hash_phys, GFP_KERNEL);
	if (!wd->hash_virt) {
		dev_warn(&wd->pdev->dev, "unable to allocate hash buffer\n");
		ret = -ENOMEM;
		goto fail_free_params;
	}

	ret = request_irq(wd->pdev->irq, wd719x_interrupt, IRQF_SHARED,
			  "wd719x", wd);
	if (ret) {
		dev_warn(&wd->pdev->dev, "unable to assign IRQ %d\n",
			 wd->pdev->irq);
		goto fail_free_hash;
	}

	/* read parameters from EEPROM */
	wd719x_read_eeprom(wd);

	ret = wd719x_chip_init(wd);
	if (ret)
		goto fail_free_irq;

	sh->this_id = wd->params->own_scsi_id & WD719X_EE_SCSI_ID_MASK;

	dev_info(&wd->pdev->dev, "%s at I/O 0x%lx, IRQ %u, SCSI ID %d\n",
		 card_types[wd->type], sh->base, sh->irq, sh->this_id);

	return 0;

fail_free_irq:
	free_irq(wd->pdev->irq, wd);
fail_free_hash:
	dma_free_coherent(&wd->pdev->dev, WD719X_HASH_TABLE_SIZE, wd->hash_virt,
			    wd->hash_phys);
fail_free_params:
	dma_free_coherent(&wd->pdev->dev, sizeof(struct wd719x_host_param),
			    wd->params, wd->params_phys);

	return ret;
}