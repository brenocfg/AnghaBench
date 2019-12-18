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
struct rackmeter_dma {int dummy; } ;
struct rackmeter {scalar_t__ ubuf; int /*<<< orphan*/  dma_buf_p; int /*<<< orphan*/  dma_buf_v; int /*<<< orphan*/  i2s_regs; int /*<<< orphan*/  dma_regs; int /*<<< orphan*/  irq; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;
struct macio_dev {TYPE_1__ ofdev; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBDMA_DO_RESET (int /*<<< orphan*/ ) ; 
 struct rackmeter* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_set_drvdata (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct rackmeter*) ; 
 int /*<<< orphan*/  free_page (unsigned long) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct rackmeter*) ; 
 TYPE_2__* macio_get_pci_dev (struct macio_dev*) ; 
 int /*<<< orphan*/  macio_release_resources (struct macio_dev*) ; 
 int /*<<< orphan*/  rackmeter_stop_cpu_sniffer (struct rackmeter*) ; 

__attribute__((used)) static int rackmeter_remove(struct macio_dev* mdev)
{
	struct rackmeter *rm = dev_get_drvdata(&mdev->ofdev.dev);

	/* Stop CPU sniffer timer & work queues */
	rackmeter_stop_cpu_sniffer(rm);

	/* Clear reference to private data */
	dev_set_drvdata(&mdev->ofdev.dev, NULL);

	/* Stop/reset dbdma */
	DBDMA_DO_RESET(rm->dma_regs);

	/* Release the IRQ */
	free_irq(rm->irq, rm);

	/* Unmap registers */
	iounmap(rm->dma_regs);
	iounmap(rm->i2s_regs);

	/* Free DMA */
	dma_free_coherent(&macio_get_pci_dev(mdev)->dev,
			  sizeof(struct rackmeter_dma),
			  rm->dma_buf_v, rm->dma_buf_p);

	/* Free samples */
	free_page((unsigned long)rm->ubuf);

#if 0
	/* Release resources */
	macio_release_resources(mdev);
#endif

	/* Get rid of me */
	kfree(rm);

	return 0;
}