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
struct hinic_hwif {struct pci_dev* pdev; } ;
struct hinic_hwdev {struct hinic_hwif* hwif; } ;
typedef  enum hinic_db_state { ____Placeholder_hinic_db_state } hinic_db_state ;

/* Variables and functions */
 int /*<<< orphan*/  DB_STATE_TIMEOUT ; 
 int EFAULT ; 
 int HINIC_DB_ENABLE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int hinic_db_state_get (struct hinic_hwif*) ; 
 unsigned long jiffies ; 
 unsigned long msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 
 scalar_t__ time_before (unsigned long,unsigned long) ; 

__attribute__((used)) static int wait_for_db_state(struct hinic_hwdev *hwdev)
{
	struct hinic_hwif *hwif = hwdev->hwif;
	struct pci_dev *pdev = hwif->pdev;
	enum hinic_db_state db_state;
	unsigned long end;

	end = jiffies + msecs_to_jiffies(DB_STATE_TIMEOUT);
	do {
		db_state = hinic_db_state_get(hwif);

		if (db_state == HINIC_DB_ENABLE)
			return 0;

		msleep(20);
	} while (time_before(jiffies, end));

	dev_err(&pdev->dev, "Wait for DB - Timeout\n");
	return -EFAULT;
}