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
typedef  int uint64_t ;
typedef  int uint16_t ;
typedef  scalar_t__ u64 ;
struct pnv_ioda_pe {int pe_number; int /*<<< orphan*/  tce_bypass_base; TYPE_1__* phb; } ;
struct pci_dev {int dummy; } ;
struct device_node {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_2__ {int /*<<< orphan*/  opal_id; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENXIO ; 
 scalar_t__ be32_to_cpu (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/ * of_get_property (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 int opal_error_code (int) ; 
 int opal_pci_map_pe_dma_window_real (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int) ; 
 struct pnv_ioda_pe* pnv_ioda_get_pe (struct pci_dev*) ; 
 struct device_node* pnv_pci_get_phb_node (struct pci_dev*) ; 
 int /*<<< orphan*/  radix_enabled () ; 

int pnv_pci_enable_tunnel(struct pci_dev *dev, u64 *asnind)
{
	struct device_node *np;
	const __be32 *prop;
	struct pnv_ioda_pe *pe;
	uint16_t window_id;
	int rc;

	if (!radix_enabled())
		return -ENXIO;

	if (!(np = pnv_pci_get_phb_node(dev)))
		return -ENXIO;

	prop = of_get_property(np, "ibm,phb-indications", NULL);
	of_node_put(np);

	if (!prop || !prop[1])
		return -ENXIO;

	*asnind = (u64)be32_to_cpu(prop[1]);
	pe = pnv_ioda_get_pe(dev);
	if (!pe)
		return -ENODEV;

	/* Increase real window size to accept as_notify messages. */
	window_id = (pe->pe_number << 1 ) + 1;
	rc = opal_pci_map_pe_dma_window_real(pe->phb->opal_id, pe->pe_number,
					     window_id, pe->tce_bypass_base,
					     (uint64_t)1 << 48);
	return opal_error_code(rc);
}