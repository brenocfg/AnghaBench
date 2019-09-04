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
struct rdc_host_priv {int /*<<< orphan*/  saved_iocfg; } ;
struct pci_dev {int dummy; } ;
struct ata_host {struct rdc_host_priv* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  ata_pci_remove_one (struct pci_dev*) ; 
 struct ata_host* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_write_config_dword (struct pci_dev*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rdc_remove_one(struct pci_dev *pdev)
{
	struct ata_host *host = pci_get_drvdata(pdev);
	struct rdc_host_priv *hpriv = host->private_data;

	pci_write_config_dword(pdev, 0x54, hpriv->saved_iocfg);

	ata_pci_remove_one(pdev);
}