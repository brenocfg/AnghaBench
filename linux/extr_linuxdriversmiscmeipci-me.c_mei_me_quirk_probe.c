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
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct mei_cfg {scalar_t__ (* quirk_probe ) (struct pci_dev*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ stub1 (struct pci_dev*) ; 

__attribute__((used)) static bool mei_me_quirk_probe(struct pci_dev *pdev,
				const struct mei_cfg *cfg)
{
	if (cfg->quirk_probe && cfg->quirk_probe(pdev)) {
		dev_info(&pdev->dev, "Device doesn't have valid ME Interface\n");
		return false;
	}

	return true;
}