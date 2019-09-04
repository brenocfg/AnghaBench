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
struct mpc52xx_ata_priv {int dummy; } ;
struct ata_port {int /*<<< orphan*/  dev; TYPE_1__* host; } ;
struct ata_device {scalar_t__ dma_mode; int /*<<< orphan*/  devno; } ;
struct TYPE_2__ {struct mpc52xx_ata_priv* private_data; } ;

/* Variables and functions */
 int XFER_MW_DMA_0 ; 
 scalar_t__ XFER_UDMA_0 ; 
 int /*<<< orphan*/  dev_alert (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  mpc52xx_ata_apply_timings (struct mpc52xx_ata_priv*,int /*<<< orphan*/ ) ; 
 int mpc52xx_ata_compute_mdma_timings (struct mpc52xx_ata_priv*,int /*<<< orphan*/ ,int) ; 
 int mpc52xx_ata_compute_udma_timings (struct mpc52xx_ata_priv*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
mpc52xx_ata_set_dmamode(struct ata_port *ap, struct ata_device *adev)
{
	struct mpc52xx_ata_priv *priv = ap->host->private_data;
	int rv;

	if (adev->dma_mode >= XFER_UDMA_0) {
		int dma = adev->dma_mode - XFER_UDMA_0;
		rv = mpc52xx_ata_compute_udma_timings(priv, adev->devno, dma);
	} else {
		int dma = adev->dma_mode - XFER_MW_DMA_0;
		rv = mpc52xx_ata_compute_mdma_timings(priv, adev->devno, dma);
	}

	if (rv) {
		dev_alert(ap->dev,
			"Trying to select invalid DMA mode %d\n",
			adev->dma_mode);
		return;
	}

	mpc52xx_ata_apply_timings(priv, adev->devno);
}