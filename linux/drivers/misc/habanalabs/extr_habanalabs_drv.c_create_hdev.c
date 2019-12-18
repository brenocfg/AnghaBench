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
struct pci_dev {int /*<<< orphan*/  dev; int /*<<< orphan*/  device; } ;
struct hl_device {scalar_t__ asic_type; int disabled; int dma_mask; int id; int id_control; struct pci_dev* pdev; int /*<<< orphan*/  timeout_jiffies; scalar_t__ pldm; int /*<<< orphan*/  reset_on_lockup; int /*<<< orphan*/  major; } ;
typedef  enum hl_asic_type { ____Placeholder_hl_asic_type } hl_asic_type ;

/* Variables and functions */
 scalar_t__ ASIC_INVALID ; 
 int EBUSY ; 
 int ENODEV ; 
 int ENOMEM ; 
 int ENOSPC ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int HL_MAX_MINORS ; 
 int /*<<< orphan*/  MAX_SCHEDULE_TIMEOUT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ get_asic_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hl_devs_idr ; 
 int /*<<< orphan*/  hl_devs_idr_lock ; 
 int /*<<< orphan*/  hl_major ; 
 int idr_alloc (int /*<<< orphan*/ *,struct hl_device*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  idr_remove (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  kfree (struct hl_device*) ; 
 struct hl_device* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  reset_on_lockup ; 
 int /*<<< orphan*/  set_driver_behavior_per_device (struct hl_device*) ; 
 int timeout_locked ; 

int create_hdev(struct hl_device **dev, struct pci_dev *pdev,
		enum hl_asic_type asic_type, int minor)
{
	struct hl_device *hdev;
	int rc, main_id, ctrl_id = 0;

	*dev = NULL;

	hdev = kzalloc(sizeof(*hdev), GFP_KERNEL);
	if (!hdev)
		return -ENOMEM;

	/* First, we must find out which ASIC are we handling. This is needed
	 * to configure the behavior of the driver (kernel parameters)
	 */
	if (pdev) {
		hdev->asic_type = get_asic_type(pdev->device);
		if (hdev->asic_type == ASIC_INVALID) {
			dev_err(&pdev->dev, "Unsupported ASIC\n");
			rc = -ENODEV;
			goto free_hdev;
		}
	} else {
		hdev->asic_type = asic_type;
	}

	hdev->major = hl_major;
	hdev->reset_on_lockup = reset_on_lockup;
	hdev->pldm = 0;

	set_driver_behavior_per_device(hdev);

	if (timeout_locked)
		hdev->timeout_jiffies = msecs_to_jiffies(timeout_locked * 1000);
	else
		hdev->timeout_jiffies = MAX_SCHEDULE_TIMEOUT;

	hdev->disabled = true;
	hdev->pdev = pdev; /* can be NULL in case of simulator device */

	/* Set default DMA mask to 32 bits */
	hdev->dma_mask = 32;

	mutex_lock(&hl_devs_idr_lock);

	/* Always save 2 numbers, 1 for main device and 1 for control.
	 * They must be consecutive
	 */
	main_id = idr_alloc(&hl_devs_idr, hdev, 0, HL_MAX_MINORS,
				GFP_KERNEL);

	if (main_id >= 0)
		ctrl_id = idr_alloc(&hl_devs_idr, hdev, main_id + 1,
					main_id + 2, GFP_KERNEL);

	mutex_unlock(&hl_devs_idr_lock);

	if ((main_id < 0) || (ctrl_id < 0)) {
		if ((main_id == -ENOSPC) || (ctrl_id == -ENOSPC))
			pr_err("too many devices in the system\n");

		if (main_id >= 0) {
			mutex_lock(&hl_devs_idr_lock);
			idr_remove(&hl_devs_idr, main_id);
			mutex_unlock(&hl_devs_idr_lock);
		}

		rc = -EBUSY;
		goto free_hdev;
	}

	hdev->id = main_id;
	hdev->id_control = ctrl_id;

	*dev = hdev;

	return 0;

free_hdev:
	kfree(hdev);
	return rc;
}