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
struct pci_dev {int dummy; } ;
struct TYPE_2__ {int num_ports; } ;
struct mthca_dev {int mthca_flags; int /*<<< orphan*/  ib_dev; int /*<<< orphan*/  driver_uar; int /*<<< orphan*/  kar; int /*<<< orphan*/  driver_pd; TYPE_1__ limits; } ;

/* Variables and functions */
 int MTHCA_FLAG_MSI_X ; 
 int /*<<< orphan*/  ib_dealloc_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mthca_CLOSE_IB (struct mthca_dev*,int) ; 
 int /*<<< orphan*/  mthca_cleanup_av_table (struct mthca_dev*) ; 
 int /*<<< orphan*/  mthca_cleanup_cq_table (struct mthca_dev*) ; 
 int /*<<< orphan*/  mthca_cleanup_eq_table (struct mthca_dev*) ; 
 int /*<<< orphan*/  mthca_cleanup_mcg_table (struct mthca_dev*) ; 
 int /*<<< orphan*/  mthca_cleanup_mr_table (struct mthca_dev*) ; 
 int /*<<< orphan*/  mthca_cleanup_pd_table (struct mthca_dev*) ; 
 int /*<<< orphan*/  mthca_cleanup_qp_table (struct mthca_dev*) ; 
 int /*<<< orphan*/  mthca_cleanup_srq_table (struct mthca_dev*) ; 
 int /*<<< orphan*/  mthca_cleanup_uar_table (struct mthca_dev*) ; 
 int /*<<< orphan*/  mthca_close_hca (struct mthca_dev*) ; 
 int /*<<< orphan*/  mthca_cmd_cleanup (struct mthca_dev*) ; 
 int /*<<< orphan*/  mthca_cmd_use_polling (struct mthca_dev*) ; 
 int /*<<< orphan*/  mthca_free_agents (struct mthca_dev*) ; 
 int /*<<< orphan*/  mthca_pd_free (struct mthca_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mthca_uar_free (struct mthca_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mthca_unregister_device (struct mthca_dev*) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_free_irq_vectors (struct pci_dev*) ; 
 struct mthca_dev* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_release_regions (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __mthca_remove_one(struct pci_dev *pdev)
{
	struct mthca_dev *mdev = pci_get_drvdata(pdev);
	int p;

	if (mdev) {
		mthca_free_agents(mdev);
		mthca_unregister_device(mdev);

		for (p = 1; p <= mdev->limits.num_ports; ++p)
			mthca_CLOSE_IB(mdev, p);

		mthca_cleanup_mcg_table(mdev);
		mthca_cleanup_av_table(mdev);
		mthca_cleanup_qp_table(mdev);
		mthca_cleanup_srq_table(mdev);
		mthca_cleanup_cq_table(mdev);
		mthca_cmd_use_polling(mdev);
		mthca_cleanup_eq_table(mdev);

		mthca_pd_free(mdev, &mdev->driver_pd);

		mthca_cleanup_mr_table(mdev);
		mthca_cleanup_pd_table(mdev);

		iounmap(mdev->kar);
		mthca_uar_free(mdev, &mdev->driver_uar);
		mthca_cleanup_uar_table(mdev);
		mthca_close_hca(mdev);
		mthca_cmd_cleanup(mdev);

		if (mdev->mthca_flags & MTHCA_FLAG_MSI_X)
			pci_free_irq_vectors(pdev);

		ib_dealloc_device(&mdev->ib_dev);
		pci_release_regions(pdev);
		pci_disable_device(pdev);
		pci_set_drvdata(pdev, NULL);
	}
}