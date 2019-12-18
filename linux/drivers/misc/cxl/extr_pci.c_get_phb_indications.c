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
typedef  int u64 ;
struct pci_dev {int dummy; } ;
struct device_node {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int ENODEV ; 
 scalar_t__ be32_to_cpu (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  indications_mutex ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * of_get_property (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 struct device_node* pnv_pci_get_phb_node (struct pci_dev*) ; 

__attribute__((used)) static int get_phb_indications(struct pci_dev *dev, u64 *capiind, u64 *asnind,
			       u64 *nbwind)
{
	static u64 nbw, asn, capi = 0;
	struct device_node *np;
	const __be32 *prop;

	mutex_lock(&indications_mutex);
	if (!capi) {
		if (!(np = pnv_pci_get_phb_node(dev))) {
			mutex_unlock(&indications_mutex);
			return -ENODEV;
		}

		prop = of_get_property(np, "ibm,phb-indications", NULL);
		if (!prop) {
			nbw = 0x0300UL; /* legacy values */
			asn = 0x0400UL;
			capi = 0x0200UL;
		} else {
			nbw = (u64)be32_to_cpu(prop[2]);
			asn = (u64)be32_to_cpu(prop[1]);
			capi = (u64)be32_to_cpu(prop[0]);
		}
		of_node_put(np);
	}
	*capiind = capi;
	*asnind = asn;
	*nbwind = nbw;
	mutex_unlock(&indications_mutex);
	return 0;
}