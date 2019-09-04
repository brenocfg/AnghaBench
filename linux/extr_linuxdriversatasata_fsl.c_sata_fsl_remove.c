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
struct sata_fsl_host_priv {int /*<<< orphan*/  hcr_base; int /*<<< orphan*/  irq; int /*<<< orphan*/  rx_watermark; int /*<<< orphan*/  intr_coalescing; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct ata_host {struct sata_fsl_host_priv* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  ata_host_detach (struct ata_host*) ; 
 int /*<<< orphan*/  device_remove_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_dispose_mapping (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct sata_fsl_host_priv*) ; 
 struct ata_host* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int sata_fsl_remove(struct platform_device *ofdev)
{
	struct ata_host *host = platform_get_drvdata(ofdev);
	struct sata_fsl_host_priv *host_priv = host->private_data;

	device_remove_file(&ofdev->dev, &host_priv->intr_coalescing);
	device_remove_file(&ofdev->dev, &host_priv->rx_watermark);

	ata_host_detach(host);

	irq_dispose_mapping(host_priv->irq);
	iounmap(host_priv->hcr_base);
	kfree(host_priv);

	return 0;
}