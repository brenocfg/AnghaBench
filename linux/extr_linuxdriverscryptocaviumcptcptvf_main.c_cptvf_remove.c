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
struct cpt_vf {int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPT_VF_INT_VEC_E_DONE ; 
 int /*<<< orphan*/  CPT_VF_INT_VEC_E_MISC ; 
 int /*<<< orphan*/  cptvf_free_irq_affinity (struct cpt_vf*,int /*<<< orphan*/ ) ; 
 scalar_t__ cptvf_send_vf_down (struct cpt_vf*) ; 
 int /*<<< orphan*/  cptvf_sw_cleanup (struct cpt_vf*) ; 
 int /*<<< orphan*/  cvm_crypto_exit () ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct cpt_vf*) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_free_irq_vectors (int /*<<< orphan*/ ) ; 
 struct cpt_vf* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_irq_vector (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_release_regions (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cptvf_remove(struct pci_dev *pdev)
{
	struct cpt_vf *cptvf = pci_get_drvdata(pdev);

	if (!cptvf) {
		dev_err(&pdev->dev, "Invalid CPT-VF device\n");
		return;
	}

	/* Convey DOWN to PF */
	if (cptvf_send_vf_down(cptvf)) {
		dev_err(&pdev->dev, "PF not responding to DOWN msg");
	} else {
		cptvf_free_irq_affinity(cptvf, CPT_VF_INT_VEC_E_DONE);
		cptvf_free_irq_affinity(cptvf, CPT_VF_INT_VEC_E_MISC);
		free_irq(pci_irq_vector(pdev, CPT_VF_INT_VEC_E_DONE), cptvf);
		free_irq(pci_irq_vector(pdev, CPT_VF_INT_VEC_E_MISC), cptvf);
		pci_free_irq_vectors(cptvf->pdev);
		cptvf_sw_cleanup(cptvf);
		pci_set_drvdata(pdev, NULL);
		pci_release_regions(pdev);
		pci_disable_device(pdev);
		cvm_crypto_exit();
	}
}