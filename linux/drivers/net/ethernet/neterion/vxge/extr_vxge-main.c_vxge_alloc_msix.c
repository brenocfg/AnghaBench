#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct vxgedev {int intr_cnt; int no_of_vpath; TYPE_1__* entries; TYPE_1__* vxge_entries; int /*<<< orphan*/  pdev; } ;
struct vxge_msix_entry {int dummy; } ;
struct msix_entry {int dummy; } ;
struct TYPE_3__ {int entry; scalar_t__ in_use; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 void* VXGE_ALARM_MSIX_ID ; 
 int /*<<< orphan*/  VXGE_DRIVER_NAME ; 
 int /*<<< orphan*/  VXGE_ERR ; 
 int VXGE_HW_VPATH_MSIX_ACTIVE ; 
 scalar_t__ VXGE_USE_DEFAULT ; 
 void* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 
 scalar_t__ max_config_vpath ; 
 int /*<<< orphan*/  pci_disable_msix (int /*<<< orphan*/ ) ; 
 int pci_enable_msix_range (int /*<<< orphan*/ ,TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  vxge_close_vpaths (struct vxgedev*,int) ; 
 int /*<<< orphan*/  vxge_debug_init (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static int vxge_alloc_msix(struct vxgedev *vdev)
{
	int j, i, ret = 0;
	int msix_intr_vect = 0, temp;
	vdev->intr_cnt = 0;

start:
	/* Tx/Rx MSIX Vectors count */
	vdev->intr_cnt = vdev->no_of_vpath * 2;

	/* Alarm MSIX Vectors count */
	vdev->intr_cnt++;

	vdev->entries = kcalloc(vdev->intr_cnt, sizeof(struct msix_entry),
				GFP_KERNEL);
	if (!vdev->entries) {
		vxge_debug_init(VXGE_ERR,
			"%s: memory allocation failed",
			VXGE_DRIVER_NAME);
		ret = -ENOMEM;
		goto alloc_entries_failed;
	}

	vdev->vxge_entries = kcalloc(vdev->intr_cnt,
				     sizeof(struct vxge_msix_entry),
				     GFP_KERNEL);
	if (!vdev->vxge_entries) {
		vxge_debug_init(VXGE_ERR, "%s: memory allocation failed",
			VXGE_DRIVER_NAME);
		ret = -ENOMEM;
		goto alloc_vxge_entries_failed;
	}

	for (i = 0, j = 0; i < vdev->no_of_vpath; i++) {

		msix_intr_vect = i * VXGE_HW_VPATH_MSIX_ACTIVE;

		/* Initialize the fifo vector */
		vdev->entries[j].entry = msix_intr_vect;
		vdev->vxge_entries[j].entry = msix_intr_vect;
		vdev->vxge_entries[j].in_use = 0;
		j++;

		/* Initialize the ring vector */
		vdev->entries[j].entry = msix_intr_vect + 1;
		vdev->vxge_entries[j].entry = msix_intr_vect + 1;
		vdev->vxge_entries[j].in_use = 0;
		j++;
	}

	/* Initialize the alarm vector */
	vdev->entries[j].entry = VXGE_ALARM_MSIX_ID;
	vdev->vxge_entries[j].entry = VXGE_ALARM_MSIX_ID;
	vdev->vxge_entries[j].in_use = 0;

	ret = pci_enable_msix_range(vdev->pdev,
				    vdev->entries, 3, vdev->intr_cnt);
	if (ret < 0) {
		ret = -ENODEV;
		goto enable_msix_failed;
	} else if (ret < vdev->intr_cnt) {
		pci_disable_msix(vdev->pdev);

		vxge_debug_init(VXGE_ERR,
			"%s: MSI-X enable failed for %d vectors, ret: %d",
			VXGE_DRIVER_NAME, vdev->intr_cnt, ret);
		if (max_config_vpath != VXGE_USE_DEFAULT) {
			ret = -ENODEV;
			goto enable_msix_failed;
		}

		kfree(vdev->entries);
		kfree(vdev->vxge_entries);
		vdev->entries = NULL;
		vdev->vxge_entries = NULL;
		/* Try with less no of vector by reducing no of vpaths count */
		temp = (ret - 1)/2;
		vxge_close_vpaths(vdev, temp);
		vdev->no_of_vpath = temp;
		goto start;
	}
	return 0;

enable_msix_failed:
	kfree(vdev->vxge_entries);
alloc_vxge_entries_failed:
	kfree(vdev->entries);
alloc_entries_failed:
	return ret;
}