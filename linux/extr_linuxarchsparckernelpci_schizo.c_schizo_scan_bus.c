#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pci_pbm_info {scalar_t__ chip_type; int /*<<< orphan*/  pci_bus; TYPE_2__* op; int /*<<< orphan*/  is_66mhz_capable; } ;
struct device {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  of_node; } ;
struct TYPE_4__ {TYPE_1__ dev; } ;

/* Variables and functions */
 scalar_t__ PBM_CHIP_TYPE_TOMATILLO ; 
 int /*<<< orphan*/ * of_find_property (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pbm_config_busmastering (struct pci_pbm_info*) ; 
 int /*<<< orphan*/  pci_scan_one_pbm (struct pci_pbm_info*,struct device*) ; 
 int /*<<< orphan*/  schizo_register_error_handlers (struct pci_pbm_info*) ; 
 int /*<<< orphan*/  tomatillo_register_error_handlers (struct pci_pbm_info*) ; 

__attribute__((used)) static void schizo_scan_bus(struct pci_pbm_info *pbm, struct device *parent)
{
	pbm_config_busmastering(pbm);
	pbm->is_66mhz_capable =
		(of_find_property(pbm->op->dev.of_node, "66mhz-capable", NULL)
		 != NULL);

	pbm->pci_bus = pci_scan_one_pbm(pbm, parent);

	if (pbm->chip_type == PBM_CHIP_TYPE_TOMATILLO)
		tomatillo_register_error_handlers(pbm);
	else
		schizo_register_error_handlers(pbm);
}