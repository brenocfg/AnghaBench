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
struct pnv_phb {scalar_t__ p2p_target_count; int /*<<< orphan*/  opal_id; } ;
struct pnv_ioda_pe {scalar_t__ p2p_initiator_count; int /*<<< orphan*/  pe_number; } ;
struct pci_dev {int /*<<< orphan*/  bus; } ;
struct pci_controller {struct pnv_phb* private_data; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int ENODEV ; 
 int ENXIO ; 
 int OPAL_PCI_P2P_ENABLE ; 
 int /*<<< orphan*/  OPAL_PCI_SET_P2P ; 
 int OPAL_SUCCESS ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  opal_check_token (int /*<<< orphan*/ ) ; 
 int opal_pci_set_p2p (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  p2p_mutex ; 
 struct pci_controller* pci_bus_to_host (int /*<<< orphan*/ ) ; 
 struct pnv_ioda_pe* pnv_ioda_get_pe (struct pci_dev*) ; 
 int /*<<< orphan*/  pnv_pci_ioda2_set_bypass (struct pnv_ioda_pe*,int) ; 

int pnv_pci_set_p2p(struct pci_dev *initiator, struct pci_dev *target, u64 desc)
{
	struct pci_controller *hose;
	struct pnv_phb *phb_init, *phb_target;
	struct pnv_ioda_pe *pe_init;
	int rc;

	if (!opal_check_token(OPAL_PCI_SET_P2P))
		return -ENXIO;

	hose = pci_bus_to_host(initiator->bus);
	phb_init = hose->private_data;

	hose = pci_bus_to_host(target->bus);
	phb_target = hose->private_data;

	pe_init = pnv_ioda_get_pe(initiator);
	if (!pe_init)
		return -ENODEV;

	/*
	 * Configuring the initiator's PHB requires to adjust its
	 * TVE#1 setting. Since the same device can be an initiator
	 * several times for different target devices, we need to keep
	 * a reference count to know when we can restore the default
	 * bypass setting on its TVE#1 when disabling. Opal is not
	 * tracking PE states, so we add a reference count on the PE
	 * in linux.
	 *
	 * For the target, the configuration is per PHB, so we keep a
	 * target reference count on the PHB.
	 */
	mutex_lock(&p2p_mutex);

	if (desc & OPAL_PCI_P2P_ENABLE) {
		/* always go to opal to validate the configuration */
		rc = opal_pci_set_p2p(phb_init->opal_id, phb_target->opal_id,
				      desc, pe_init->pe_number);

		if (rc != OPAL_SUCCESS) {
			rc = -EIO;
			goto out;
		}

		pe_init->p2p_initiator_count++;
		phb_target->p2p_target_count++;
	} else {
		if (!pe_init->p2p_initiator_count ||
			!phb_target->p2p_target_count) {
			rc = -EINVAL;
			goto out;
		}

		if (--pe_init->p2p_initiator_count == 0)
			pnv_pci_ioda2_set_bypass(pe_init, true);

		if (--phb_target->p2p_target_count == 0) {
			rc = opal_pci_set_p2p(phb_init->opal_id,
					      phb_target->opal_id, desc,
					      pe_init->pe_number);
			if (rc != OPAL_SUCCESS) {
				rc = -EIO;
				goto out;
			}
		}
	}
	rc = 0;
out:
	mutex_unlock(&p2p_mutex);
	return rc;
}