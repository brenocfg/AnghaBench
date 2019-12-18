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
struct spi_device {int dummy; } ;
struct adf7242_local {int /*<<< orphan*/  hw; int /*<<< orphan*/  bmux; int /*<<< orphan*/  wqueue; int /*<<< orphan*/  work; int /*<<< orphan*/  debugfs_root; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugfs_remove_recursive (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee802154_free_hw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee802154_unregister_hw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 struct adf7242_local* spi_get_drvdata (struct spi_device*) ; 

__attribute__((used)) static int adf7242_remove(struct spi_device *spi)
{
	struct adf7242_local *lp = spi_get_drvdata(spi);

	debugfs_remove_recursive(lp->debugfs_root);

	cancel_delayed_work_sync(&lp->work);
	destroy_workqueue(lp->wqueue);

	ieee802154_unregister_hw(lp->hw);
	mutex_destroy(&lp->bmux);
	ieee802154_free_hw(lp->hw);

	return 0;
}