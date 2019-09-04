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

/* Variables and functions */
 int /*<<< orphan*/  DB1300_SD1_EJECT_INT ; 
 int /*<<< orphan*/  DB1300_SD1_INSERT_INT ; 
 scalar_t__ db1300_mmc_card_inserted (void*) ; 
 int /*<<< orphan*/  db1300_mmc_cd ; 
 int /*<<< orphan*/  db1300_mmc_cdfn ; 
 int /*<<< orphan*/  enable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,void*) ; 
 int request_threaded_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,void*) ; 

__attribute__((used)) static int db1300_mmc_cd_setup(void *mmc_host, int en)
{
	int ret;

	if (en) {
		ret = request_threaded_irq(DB1300_SD1_INSERT_INT, db1300_mmc_cd,
				db1300_mmc_cdfn, 0, "sd_insert", mmc_host);
		if (ret)
			goto out;

		ret = request_threaded_irq(DB1300_SD1_EJECT_INT, db1300_mmc_cd,
				db1300_mmc_cdfn, 0, "sd_eject", mmc_host);
		if (ret) {
			free_irq(DB1300_SD1_INSERT_INT, mmc_host);
			goto out;
		}

		if (db1300_mmc_card_inserted(mmc_host))
			enable_irq(DB1300_SD1_EJECT_INT);
		else
			enable_irq(DB1300_SD1_INSERT_INT);

	} else {
		free_irq(DB1300_SD1_INSERT_INT, mmc_host);
		free_irq(DB1300_SD1_EJECT_INT, mmc_host);
	}
	ret = 0;
out:
	return ret;
}