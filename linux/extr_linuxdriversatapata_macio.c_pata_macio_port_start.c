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
struct pata_macio_priv {int /*<<< orphan*/  dev; int /*<<< orphan*/ * dma_table_cpu; int /*<<< orphan*/  dma_table_dma; } ;
struct dbdma_cmd {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * bmdma_addr; } ;
struct ata_port {scalar_t__ udma_mask; scalar_t__ mwdma_mask; TYPE_1__ ioaddr; struct pata_macio_priv* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int MAX_DCMDS ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * dmam_alloc_coherent (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pata_macio_port_start(struct ata_port *ap)
{
	struct pata_macio_priv *priv = ap->private_data;

	if (ap->ioaddr.bmdma_addr == NULL)
		return 0;

	/* Allocate space for the DBDMA commands.
	 *
	 * The +2 is +1 for the stop command and +1 to allow for
	 * aligning the start address to a multiple of 16 bytes.
	 */
	priv->dma_table_cpu =
		dmam_alloc_coherent(priv->dev,
				    (MAX_DCMDS + 2) * sizeof(struct dbdma_cmd),
				    &priv->dma_table_dma, GFP_KERNEL);
	if (priv->dma_table_cpu == NULL) {
		dev_err(priv->dev, "Unable to allocate DMA command list\n");
		ap->ioaddr.bmdma_addr = NULL;
		ap->mwdma_mask = 0;
		ap->udma_mask = 0;
	}
	return 0;
}