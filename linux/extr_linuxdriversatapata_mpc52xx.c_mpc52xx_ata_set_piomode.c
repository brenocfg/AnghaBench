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
struct ata_device {int pio_mode; int /*<<< orphan*/  devno; } ;
struct TYPE_2__ {struct mpc52xx_ata_priv* private_data; } ;

/* Variables and functions */
 int XFER_PIO_0 ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  mpc52xx_ata_apply_timings (struct mpc52xx_ata_priv*,int /*<<< orphan*/ ) ; 
 int mpc52xx_ata_compute_pio_timings (struct mpc52xx_ata_priv*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
mpc52xx_ata_set_piomode(struct ata_port *ap, struct ata_device *adev)
{
	struct mpc52xx_ata_priv *priv = ap->host->private_data;
	int pio, rv;

	pio = adev->pio_mode - XFER_PIO_0;

	rv = mpc52xx_ata_compute_pio_timings(priv, adev->devno, pio);

	if (rv) {
		dev_err(ap->dev, "error: invalid PIO mode: %d\n", pio);
		return;
	}

	mpc52xx_ata_apply_timings(priv, adev->devno);
}