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
struct pci_dev {int dummy; } ;
struct dw_spi {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dw_spi_remove_host (struct dw_spi*) ; 
 struct dw_spi* pci_get_drvdata (struct pci_dev*) ; 

__attribute__((used)) static void spi_pci_remove(struct pci_dev *pdev)
{
	struct dw_spi *dws = pci_get_drvdata(pdev);

	dw_spi_remove_host(dws);
}