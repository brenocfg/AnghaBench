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
struct owl_ctx {int /*<<< orphan*/  eeprom_load; } ;

/* Variables and functions */
 struct owl_ctx* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void owl_remove(struct pci_dev *pdev)
{
	struct owl_ctx *ctx = pci_get_drvdata(pdev);

	if (ctx) {
		wait_for_completion(&ctx->eeprom_load);
		pci_set_drvdata(pdev, NULL);
	}
}