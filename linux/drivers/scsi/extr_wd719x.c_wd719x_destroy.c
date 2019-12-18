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
struct wd719x_host_param {int dummy; } ;
struct wd719x {int fw_size; TYPE_1__* pdev; int /*<<< orphan*/ * params; int /*<<< orphan*/  params_phys; int /*<<< orphan*/ * hash_virt; int /*<<< orphan*/  hash_phys; int /*<<< orphan*/ * fw_virt; int /*<<< orphan*/  fw_phys; int /*<<< orphan*/  active_scbs; } ;
struct TYPE_2__ {int /*<<< orphan*/  irq; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  WD719X_CMD_SLEEP ; 
 int WD719X_HASH_TABLE_SIZE ; 
 int /*<<< orphan*/  WD719X_PCI_MODE_SELECT ; 
 int /*<<< orphan*/  WD719X_WAIT_FOR_RISC ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct wd719x*) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 scalar_t__ wd719x_direct_cmd (struct wd719x*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wd719x_writeb (struct wd719x*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wd719x_destroy(struct wd719x *wd)
{
	/* stop the RISC */
	if (wd719x_direct_cmd(wd, WD719X_CMD_SLEEP, 0, 0, 0, 0,
			      WD719X_WAIT_FOR_RISC))
		dev_warn(&wd->pdev->dev, "RISC sleep command failed\n");
	/* disable RISC */
	wd719x_writeb(wd, WD719X_PCI_MODE_SELECT, 0);

	WARN_ON_ONCE(!list_empty(&wd->active_scbs));

	/* free internal buffers */
	dma_free_coherent(&wd->pdev->dev, wd->fw_size, wd->fw_virt,
			  wd->fw_phys);
	wd->fw_virt = NULL;
	dma_free_coherent(&wd->pdev->dev, WD719X_HASH_TABLE_SIZE, wd->hash_virt,
			  wd->hash_phys);
	wd->hash_virt = NULL;
	dma_free_coherent(&wd->pdev->dev, sizeof(struct wd719x_host_param),
			  wd->params, wd->params_phys);
	wd->params = NULL;
	free_irq(wd->pdev->irq, wd);
}