#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  syncp; } ;
struct TYPE_4__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  list; } ;
struct slic_device {TYPE_3__* pdev; TYPE_2__ stats; TYPE_1__ upr_list; int /*<<< orphan*/  link_lock; int /*<<< orphan*/  upper_lock; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  slic_card_reset (struct slic_device*) ; 
 int /*<<< orphan*/  slic_free_shmem (struct slic_device*) ; 
 int slic_init_shmem (struct slic_device*) ; 
 int slic_load_firmware (struct slic_device*) ; 
 int slic_read_eeprom (struct slic_device*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  u64_stats_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int slic_init(struct slic_device *sdev)
{
	int err;

	spin_lock_init(&sdev->upper_lock);
	spin_lock_init(&sdev->link_lock);
	INIT_LIST_HEAD(&sdev->upr_list.list);
	spin_lock_init(&sdev->upr_list.lock);
	u64_stats_init(&sdev->stats.syncp);

	slic_card_reset(sdev);

	err = slic_load_firmware(sdev);
	if (err) {
		dev_err(&sdev->pdev->dev, "failed to load firmware\n");
		return err;
	}

	/* we need the shared memory to read EEPROM so set it up temporarily */
	err = slic_init_shmem(sdev);
	if (err) {
		dev_err(&sdev->pdev->dev, "failed to init shared memory\n");
		return err;
	}

	err = slic_read_eeprom(sdev);
	if (err) {
		dev_err(&sdev->pdev->dev, "failed to read eeprom\n");
		goto free_sm;
	}

	slic_card_reset(sdev);
	slic_free_shmem(sdev);

	return 0;
free_sm:
	slic_free_shmem(sdev);

	return err;
}