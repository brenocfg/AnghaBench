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
struct hinic_hwdev {int /*<<< orphan*/  aeqs; int /*<<< orphan*/  msix_entries; struct hinic_hwif* hwif; } ;
struct hinic_pfhwdev {struct hinic_hwdev hwdev; } ;
struct hinic_hwif {int dummy; } ;

/* Variables and functions */
 int EFAULT ; 
 int ENOMEM ; 
 struct hinic_hwdev* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HINIC_DEFAULT_AEQ_LEN ; 
 int /*<<< orphan*/  HINIC_EQ_PAGE_SIZE ; 
 int HINIC_HWIF_NUM_AEQS (struct hinic_hwif*) ; 
 int /*<<< orphan*/  HINIC_IS_PF (struct hinic_hwif*) ; 
 int /*<<< orphan*/  HINIC_IS_PPF (struct hinic_hwif*) ; 
 int /*<<< orphan*/  HINIC_OUTBOUND_ENABLE ; 
 int /*<<< orphan*/  HINIC_RES_ACTIVE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 void* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  disable_msix (struct hinic_hwdev*) ; 
 int /*<<< orphan*/  free_pfhwdev (struct hinic_pfhwdev*) ; 
 int get_dev_cap (struct hinic_hwdev*) ; 
 int /*<<< orphan*/  hinic_aeqs_free (int /*<<< orphan*/ *) ; 
 int hinic_aeqs_init (int /*<<< orphan*/ *,struct hinic_hwif*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hinic_free_hwif (struct hinic_hwif*) ; 
 int hinic_init_hwif (struct hinic_hwif*,struct pci_dev*) ; 
 int /*<<< orphan*/  hinic_outbound_state_set (struct hinic_hwif*,int /*<<< orphan*/ ) ; 
 int init_fw_ctxt (struct hinic_hwdev*) ; 
 int init_msix (struct hinic_hwdev*) ; 
 int init_pfhwdev (struct hinic_pfhwdev*) ; 
 int set_resources_state (struct hinic_hwdev*,int /*<<< orphan*/ ) ; 
 int wait_for_outbound_state (struct hinic_hwdev*) ; 

struct hinic_hwdev *hinic_init_hwdev(struct pci_dev *pdev)
{
	struct hinic_pfhwdev *pfhwdev;
	struct hinic_hwdev *hwdev;
	struct hinic_hwif *hwif;
	int err, num_aeqs;

	hwif = devm_kzalloc(&pdev->dev, sizeof(*hwif), GFP_KERNEL);
	if (!hwif)
		return ERR_PTR(-ENOMEM);

	err = hinic_init_hwif(hwif, pdev);
	if (err) {
		dev_err(&pdev->dev, "Failed to init HW interface\n");
		return ERR_PTR(err);
	}

	if (!HINIC_IS_PF(hwif) && !HINIC_IS_PPF(hwif)) {
		dev_err(&pdev->dev, "Unsupported PCI Function type\n");
		err = -EFAULT;
		goto err_func_type;
	}

	pfhwdev = devm_kzalloc(&pdev->dev, sizeof(*pfhwdev), GFP_KERNEL);
	if (!pfhwdev) {
		err = -ENOMEM;
		goto err_pfhwdev_alloc;
	}

	hwdev = &pfhwdev->hwdev;
	hwdev->hwif = hwif;

	err = init_msix(hwdev);
	if (err) {
		dev_err(&pdev->dev, "Failed to init msix\n");
		goto err_init_msix;
	}

	err = wait_for_outbound_state(hwdev);
	if (err) {
		dev_warn(&pdev->dev, "outbound - disabled, try again\n");
		hinic_outbound_state_set(hwif, HINIC_OUTBOUND_ENABLE);
	}

	num_aeqs = HINIC_HWIF_NUM_AEQS(hwif);

	err = hinic_aeqs_init(&hwdev->aeqs, hwif, num_aeqs,
			      HINIC_DEFAULT_AEQ_LEN, HINIC_EQ_PAGE_SIZE,
			      hwdev->msix_entries);
	if (err) {
		dev_err(&pdev->dev, "Failed to init async event queues\n");
		goto err_aeqs_init;
	}

	err = init_pfhwdev(pfhwdev);
	if (err) {
		dev_err(&pdev->dev, "Failed to init PF HW device\n");
		goto err_init_pfhwdev;
	}

	err = get_dev_cap(hwdev);
	if (err) {
		dev_err(&pdev->dev, "Failed to get device capabilities\n");
		goto err_dev_cap;
	}

	err = init_fw_ctxt(hwdev);
	if (err) {
		dev_err(&pdev->dev, "Failed to init function table\n");
		goto err_init_fw_ctxt;
	}

	err = set_resources_state(hwdev, HINIC_RES_ACTIVE);
	if (err) {
		dev_err(&pdev->dev, "Failed to set resources state\n");
		goto err_resources_state;
	}

	return hwdev;

err_resources_state:
err_init_fw_ctxt:
err_dev_cap:
	free_pfhwdev(pfhwdev);

err_init_pfhwdev:
	hinic_aeqs_free(&hwdev->aeqs);

err_aeqs_init:
	disable_msix(hwdev);

err_init_msix:
err_pfhwdev_alloc:
err_func_type:
	hinic_free_hwif(hwif);
	return ERR_PTR(err);
}