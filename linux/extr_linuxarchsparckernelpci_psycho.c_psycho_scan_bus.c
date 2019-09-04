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
struct pci_pbm_info {int /*<<< orphan*/  pci_bus; scalar_t__ is_66mhz_capable; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  pbm_config_busmastering (struct pci_pbm_info*) ; 
 int /*<<< orphan*/  pci_scan_one_pbm (struct pci_pbm_info*,struct device*) ; 
 int /*<<< orphan*/  psycho_register_error_handlers (struct pci_pbm_info*) ; 

__attribute__((used)) static void psycho_scan_bus(struct pci_pbm_info *pbm,
			    struct device *parent)
{
	pbm_config_busmastering(pbm);
	pbm->is_66mhz_capable = 0;
	pbm->pci_bus = pci_scan_one_pbm(pbm, parent);

	/* After the PCI bus scan is complete, we can register
	 * the error interrupt handlers.
	 */
	psycho_register_error_handlers(pbm);
}