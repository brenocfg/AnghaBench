#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pci_dev {int dummy; } ;
struct TYPE_3__ {scalar_t__ dma; } ;
typedef  TYPE_1__ avmcard ;

/* Variables and functions */
 int /*<<< orphan*/  b1pci_remove (struct pci_dev*) ; 
 int /*<<< orphan*/  b1pciv4_remove (struct pci_dev*) ; 
 TYPE_1__* pci_get_drvdata (struct pci_dev*) ; 

__attribute__((used)) static void b1pci_pci_remove(struct pci_dev *pdev)
{
#ifdef CONFIG_ISDN_DRV_AVMB1_B1PCIV4
	avmcard *card = pci_get_drvdata(pdev);

	if (card->dma)
		b1pciv4_remove(pdev);
	else
		b1pci_remove(pdev);
#else
	b1pci_remove(pdev);
#endif
}