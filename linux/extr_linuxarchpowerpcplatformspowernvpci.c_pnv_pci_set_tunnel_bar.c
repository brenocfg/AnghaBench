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
struct pnv_phb {int /*<<< orphan*/  opal_id; } ;
struct pci_dev {int /*<<< orphan*/  bus; } ;
struct pci_controller {struct pnv_phb* private_data; } ;
typedef  int /*<<< orphan*/  __be64 ;

/* Variables and functions */
 int EBUSY ; 
 int EIO ; 
 int ENXIO ; 
 int EPERM ; 
 int /*<<< orphan*/  OPAL_PCI_GET_PBCQ_TUNNEL_BAR ; 
 int /*<<< orphan*/  OPAL_PCI_SET_PBCQ_TUNNEL_BAR ; 
 int OPAL_SUCCESS ; 
 int be64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  opal_check_token (int /*<<< orphan*/ ) ; 
 int opal_error_code (int) ; 
 int opal_pci_get_pbcq_tunnel_bar (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int opal_pci_set_pbcq_tunnel_bar (int /*<<< orphan*/ ,int) ; 
 struct pci_controller* pci_bus_to_host (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tunnel_mutex ; 

int pnv_pci_set_tunnel_bar(struct pci_dev *dev, u64 addr, int enable)
{
	__be64 val;
	struct pci_controller *hose;
	struct pnv_phb *phb;
	u64 tunnel_bar;
	int rc;

	if (!opal_check_token(OPAL_PCI_GET_PBCQ_TUNNEL_BAR))
		return -ENXIO;
	if (!opal_check_token(OPAL_PCI_SET_PBCQ_TUNNEL_BAR))
		return -ENXIO;

	hose = pci_bus_to_host(dev->bus);
	phb = hose->private_data;

	mutex_lock(&tunnel_mutex);
	rc = opal_pci_get_pbcq_tunnel_bar(phb->opal_id, &val);
	if (rc != OPAL_SUCCESS) {
		rc = -EIO;
		goto out;
	}
	tunnel_bar = be64_to_cpu(val);
	if (enable) {
		/*
		* Only one device per PHB can use atomics.
		* Our policy is first-come, first-served.
		*/
		if (tunnel_bar) {
			if (tunnel_bar != addr)
				rc = -EBUSY;
			else
				rc = 0;	/* Setting same address twice is ok */
			goto out;
		}
	} else {
		/*
		* The device that owns atomics and wants to release
		* them must pass the same address with enable == 0.
		*/
		if (tunnel_bar != addr) {
			rc = -EPERM;
			goto out;
		}
		addr = 0x0ULL;
	}
	rc = opal_pci_set_pbcq_tunnel_bar(phb->opal_id, addr);
	rc = opal_error_code(rc);
out:
	mutex_unlock(&tunnel_mutex);
	return rc;
}