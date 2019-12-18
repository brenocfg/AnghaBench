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
typedef  int u32 ;
struct pci_device_id {scalar_t__ driver_data; } ;
struct pci_dev {int /*<<< orphan*/ * resource; int /*<<< orphan*/  dev; } ;
struct intel_spi_boardinfo {int writeable; } ;
struct intel_spi {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BCR ; 
 int BCR_WPD ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct intel_spi*) ; 
 int PTR_ERR (struct intel_spi*) ; 
 struct intel_spi_boardinfo* devm_kmemdup (int /*<<< orphan*/ *,void*,int,int /*<<< orphan*/ ) ; 
 struct intel_spi* intel_spi_probe (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct intel_spi_boardinfo*) ; 
 int /*<<< orphan*/  pci_read_config_dword (struct pci_dev*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,struct intel_spi*) ; 
 int /*<<< orphan*/  pci_write_config_dword (struct pci_dev*,int /*<<< orphan*/ ,int) ; 
 int pcim_enable_device (struct pci_dev*) ; 

__attribute__((used)) static int intel_spi_pci_probe(struct pci_dev *pdev,
			       const struct pci_device_id *id)
{
	struct intel_spi_boardinfo *info;
	struct intel_spi *ispi;
	u32 bcr;
	int ret;

	ret = pcim_enable_device(pdev);
	if (ret)
		return ret;

	info = devm_kmemdup(&pdev->dev, (void *)id->driver_data, sizeof(*info),
			    GFP_KERNEL);
	if (!info)
		return -ENOMEM;

	/* Try to make the chip read/write */
	pci_read_config_dword(pdev, BCR, &bcr);
	if (!(bcr & BCR_WPD)) {
		bcr |= BCR_WPD;
		pci_write_config_dword(pdev, BCR, bcr);
		pci_read_config_dword(pdev, BCR, &bcr);
	}
	info->writeable = !!(bcr & BCR_WPD);

	ispi = intel_spi_probe(&pdev->dev, &pdev->resource[0], info);
	if (IS_ERR(ispi))
		return PTR_ERR(ispi);

	pci_set_drvdata(pdev, ispi);
	return 0;
}