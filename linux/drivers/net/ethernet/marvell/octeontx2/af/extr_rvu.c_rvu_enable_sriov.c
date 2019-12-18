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
struct rvu {int vfs; int /*<<< orphan*/  afvf_wq_info; struct pci_dev* pdev; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  TYPE_AFVF ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,...) ; 
 int lbk_get_num_chans () ; 
 int /*<<< orphan*/  mb () ; 
 int pci_enable_sriov (struct pci_dev*,int) ; 
 int pci_sriov_get_totalvfs (struct pci_dev*) ; 
 int /*<<< orphan*/  rvu_afvf_mbox_handler ; 
 int /*<<< orphan*/  rvu_afvf_mbox_up_handler ; 
 int /*<<< orphan*/  rvu_afvf_msix_vectors_num_ok (struct rvu*) ; 
 int /*<<< orphan*/  rvu_disable_afvf_intr (struct rvu*) ; 
 int /*<<< orphan*/  rvu_enable_afvf_intr (struct rvu*) ; 
 int /*<<< orphan*/  rvu_mbox_destroy (int /*<<< orphan*/ *) ; 
 int rvu_mbox_init (struct rvu*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rvu_enable_sriov(struct rvu *rvu)
{
	struct pci_dev *pdev = rvu->pdev;
	int err, chans, vfs;

	if (!rvu_afvf_msix_vectors_num_ok(rvu)) {
		dev_warn(&pdev->dev,
			 "Skipping SRIOV enablement since not enough IRQs are available\n");
		return 0;
	}

	chans = lbk_get_num_chans();
	if (chans < 0)
		return chans;

	vfs = pci_sriov_get_totalvfs(pdev);

	/* Limit VFs in case we have more VFs than LBK channels available. */
	if (vfs > chans)
		vfs = chans;

	/* AF's VFs work in pairs and talk over consecutive loopback channels.
	 * Thus we want to enable maximum even number of VFs. In case
	 * odd number of VFs are available then the last VF on the list
	 * remains disabled.
	 */
	if (vfs & 0x1) {
		dev_warn(&pdev->dev,
			 "Number of VFs should be even. Enabling %d out of %d.\n",
			 vfs - 1, vfs);
		vfs--;
	}

	if (!vfs)
		return 0;

	/* Save VFs number for reference in VF interrupts handlers.
	 * Since interrupts might start arriving during SRIOV enablement
	 * ordinary API cannot be used to get number of enabled VFs.
	 */
	rvu->vfs = vfs;

	err = rvu_mbox_init(rvu, &rvu->afvf_wq_info, TYPE_AFVF, vfs,
			    rvu_afvf_mbox_handler, rvu_afvf_mbox_up_handler);
	if (err)
		return err;

	rvu_enable_afvf_intr(rvu);
	/* Make sure IRQs are enabled before SRIOV. */
	mb();

	err = pci_enable_sriov(pdev, vfs);
	if (err) {
		rvu_disable_afvf_intr(rvu);
		rvu_mbox_destroy(&rvu->afvf_wq_info);
		return err;
	}

	return 0;
}