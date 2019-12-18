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
typedef  scalar_t__ u32 ;
struct mlx5_core_dev {int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  VSC_COUNTER_OFFSET ; 
 int VSC_MAX_RETRIES ; 
 int /*<<< orphan*/  VSC_SEMAPHORE_OFFSET ; 
 int /*<<< orphan*/  pci_cfg_access_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_cfg_access_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 
 int vsc_read (struct mlx5_core_dev*,int /*<<< orphan*/ ,scalar_t__*) ; 
 int vsc_write (struct mlx5_core_dev*,int /*<<< orphan*/ ,scalar_t__) ; 

int mlx5_vsc_gw_lock(struct mlx5_core_dev *dev)
{
	u32 counter = 0;
	int retries = 0;
	u32 lock_val;
	int ret;

	pci_cfg_access_lock(dev->pdev);
	do {
		if (retries > VSC_MAX_RETRIES) {
			ret = -EBUSY;
			goto pci_unlock;
		}

		/* Check if semaphore is already locked */
		ret = vsc_read(dev, VSC_SEMAPHORE_OFFSET, &lock_val);
		if (ret)
			goto pci_unlock;

		if (lock_val) {
			retries++;
			usleep_range(1000, 2000);
			continue;
		}

		/* Read and write counter value, if written value is
		 * the same, semaphore was acquired successfully.
		 */
		ret = vsc_read(dev, VSC_COUNTER_OFFSET, &counter);
		if (ret)
			goto pci_unlock;

		ret = vsc_write(dev, VSC_SEMAPHORE_OFFSET, counter);
		if (ret)
			goto pci_unlock;

		ret = vsc_read(dev, VSC_SEMAPHORE_OFFSET, &lock_val);
		if (ret)
			goto pci_unlock;

		retries++;
	} while (counter != lock_val);

	return 0;

pci_unlock:
	pci_cfg_access_unlock(dev->pdev);
	return ret;
}