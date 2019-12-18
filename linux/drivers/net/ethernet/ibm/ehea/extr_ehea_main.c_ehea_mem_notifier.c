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
struct notifier_block {int dummy; } ;
struct memory_notify {int /*<<< orphan*/  nr_pages; int /*<<< orphan*/  start_pfn; } ;

/* Variables and functions */
#define  MEM_CANCEL_OFFLINE 130 
#define  MEM_GOING_OFFLINE 129 
#define  MEM_ONLINE 128 
 int NOTIFY_BAD ; 
 int NOTIFY_OK ; 
 int /*<<< orphan*/  __EHEA_STOP_XFER ; 
 int /*<<< orphan*/  dlpar_mem_lock ; 
 int /*<<< orphan*/  ehea_add_sect_bmap (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ehea_driver_flags ; 
 int /*<<< orphan*/  ehea_rem_sect_bmap (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ehea_rereg_mrs () ; 
 int /*<<< orphan*/  ehea_update_firmware_handles () ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ehea_mem_notifier(struct notifier_block *nb,
			     unsigned long action, void *data)
{
	int ret = NOTIFY_BAD;
	struct memory_notify *arg = data;

	mutex_lock(&dlpar_mem_lock);

	switch (action) {
	case MEM_CANCEL_OFFLINE:
		pr_info("memory offlining canceled");
		/* Fall through - re-add canceled memory block */

	case MEM_ONLINE:
		pr_info("memory is going online");
		set_bit(__EHEA_STOP_XFER, &ehea_driver_flags);
		if (ehea_add_sect_bmap(arg->start_pfn, arg->nr_pages))
			goto out_unlock;
		ehea_rereg_mrs();
		break;

	case MEM_GOING_OFFLINE:
		pr_info("memory is going offline");
		set_bit(__EHEA_STOP_XFER, &ehea_driver_flags);
		if (ehea_rem_sect_bmap(arg->start_pfn, arg->nr_pages))
			goto out_unlock;
		ehea_rereg_mrs();
		break;

	default:
		break;
	}

	ehea_update_firmware_handles();
	ret = NOTIFY_OK;

out_unlock:
	mutex_unlock(&dlpar_mem_lock);
	return ret;
}