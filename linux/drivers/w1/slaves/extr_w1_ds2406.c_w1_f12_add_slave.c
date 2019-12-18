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
struct TYPE_2__ {int /*<<< orphan*/  kobj; } ;
struct w1_slave {TYPE_1__ dev; } ;

/* Variables and functions */
 int NB_SYSFS_BIN_FILES ; 
 int sysfs_create_bin_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sysfs_remove_bin_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * w1_f12_sysfs_bin_files ; 

__attribute__((used)) static int w1_f12_add_slave(struct w1_slave *sl)
{
	int err = 0;
	int i;

	for (i = 0; i < NB_SYSFS_BIN_FILES && !err; ++i)
		err = sysfs_create_bin_file(
			&sl->dev.kobj,
			&(w1_f12_sysfs_bin_files[i]));
	if (err)
		while (--i >= 0)
			sysfs_remove_bin_file(&sl->dev.kobj,
				&(w1_f12_sysfs_bin_files[i]));
	return err;
}