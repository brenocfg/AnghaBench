#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct se_lun {int /*<<< orphan*/  lun_se_dev; } ;
struct se_device {TYPE_2__* se_hba; TYPE_1__* transport; } ;
typedef  int ssize_t ;
struct TYPE_4__ {int hba_flags; } ;
struct TYPE_3__ {int transport_flags; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int HBA_FLAGS_INTERNAL_USE ; 
 int TRANSPORT_FLAG_PASSTHROUGH_ALUA ; 
 int core_alua_set_tg_pt_secondary_state (struct se_lun*,int /*<<< orphan*/ ,int) ; 
 int kstrtoul (char const*,int /*<<< orphan*/ ,unsigned long*) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 struct se_device* rcu_dereference_raw (int /*<<< orphan*/ ) ; 

ssize_t core_alua_store_offline_bit(
	struct se_lun *lun,
	const char *page,
	size_t count)
{
	/*
	 * rcu_dereference_raw protected by se_lun->lun_group symlink
	 * reference to se_device->dev_group.
	 */
	struct se_device *dev = rcu_dereference_raw(lun->lun_se_dev);
	unsigned long tmp;
	int ret;

	if (dev->transport->transport_flags & TRANSPORT_FLAG_PASSTHROUGH_ALUA ||
	    (dev->se_hba->hba_flags & HBA_FLAGS_INTERNAL_USE))
		return -ENODEV;

	ret = kstrtoul(page, 0, &tmp);
	if (ret < 0) {
		pr_err("Unable to extract alua_tg_pt_offline value\n");
		return ret;
	}
	if ((tmp != 0) && (tmp != 1)) {
		pr_err("Illegal value for alua_tg_pt_offline: %lu\n",
				tmp);
		return -EINVAL;
	}

	ret = core_alua_set_tg_pt_secondary_state(lun, 0, (int)tmp);
	if (ret < 0)
		return -EINVAL;

	return count;
}