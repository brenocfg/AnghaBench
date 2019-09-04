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
struct mem_ctl_info {size_t mc_idx; scalar_t__ mod_name; int /*<<< orphan*/  op_state; int /*<<< orphan*/  dev_name; int /*<<< orphan*/  ctl_name; int /*<<< orphan*/  work; scalar_t__ edac_check; int /*<<< orphan*/ * bus; int /*<<< orphan*/  start_time; } ;
struct attribute_group {int dummy; } ;

/* Variables and functions */
 size_t EDAC_MAX_MCS ; 
 int EINVAL ; 
 int ENODEV ; 
 int EPERM ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  KERN_WARNING ; 
 int /*<<< orphan*/  OP_RUNNING_INTERRUPT ; 
 int /*<<< orphan*/  OP_RUNNING_POLL ; 
 scalar_t__ add_mc_to_global_list (struct mem_ctl_info*) ; 
 int /*<<< orphan*/  del_mc_from_global_list (struct mem_ctl_info*) ; 
 scalar_t__ edac_create_sysfs_mci_device (struct mem_ctl_info*,struct attribute_group const**) ; 
 int /*<<< orphan*/  edac_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  edac_mc_get_poll_msec () ; 
 scalar_t__ edac_mc_owner ; 
 int /*<<< orphan*/  edac_mc_printk (struct mem_ctl_info*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  edac_mc_workq_function ; 
 int /*<<< orphan*/  edac_op_state_to_string (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  edac_queue_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/ * mc_bus ; 
 int /*<<< orphan*/  mem_ctls_mutex ; 
 int /*<<< orphan*/  msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_warn_once (char*,size_t) ; 

int edac_mc_add_mc_with_groups(struct mem_ctl_info *mci,
			       const struct attribute_group **groups)
{
	int ret = -EINVAL;
	edac_dbg(0, "\n");

	if (mci->mc_idx >= EDAC_MAX_MCS) {
		pr_warn_once("Too many memory controllers: %d\n", mci->mc_idx);
		return -ENODEV;
	}

#ifdef CONFIG_EDAC_DEBUG
	if (edac_debug_level >= 3)
		edac_mc_dump_mci(mci);

	if (edac_debug_level >= 4) {
		int i;

		for (i = 0; i < mci->nr_csrows; i++) {
			struct csrow_info *csrow = mci->csrows[i];
			u32 nr_pages = 0;
			int j;

			for (j = 0; j < csrow->nr_channels; j++)
				nr_pages += csrow->channels[j]->dimm->nr_pages;
			if (!nr_pages)
				continue;
			edac_mc_dump_csrow(csrow);
			for (j = 0; j < csrow->nr_channels; j++)
				if (csrow->channels[j]->dimm->nr_pages)
					edac_mc_dump_channel(csrow->channels[j]);
		}
		for (i = 0; i < mci->tot_dimms; i++)
			if (mci->dimms[i]->nr_pages)
				edac_mc_dump_dimm(mci->dimms[i], i);
	}
#endif
	mutex_lock(&mem_ctls_mutex);

	if (edac_mc_owner && edac_mc_owner != mci->mod_name) {
		ret = -EPERM;
		goto fail0;
	}

	if (add_mc_to_global_list(mci))
		goto fail0;

	/* set load time so that error rate can be tracked */
	mci->start_time = jiffies;

	mci->bus = &mc_bus[mci->mc_idx];

	if (edac_create_sysfs_mci_device(mci, groups)) {
		edac_mc_printk(mci, KERN_WARNING,
			"failed to create sysfs device\n");
		goto fail1;
	}

	if (mci->edac_check) {
		mci->op_state = OP_RUNNING_POLL;

		INIT_DELAYED_WORK(&mci->work, edac_mc_workq_function);
		edac_queue_work(&mci->work, msecs_to_jiffies(edac_mc_get_poll_msec()));

	} else {
		mci->op_state = OP_RUNNING_INTERRUPT;
	}

	/* Report action taken */
	edac_mc_printk(mci, KERN_INFO,
		"Giving out device to module %s controller %s: DEV %s (%s)\n",
		mci->mod_name, mci->ctl_name, mci->dev_name,
		edac_op_state_to_string(mci->op_state));

	edac_mc_owner = mci->mod_name;

	mutex_unlock(&mem_ctls_mutex);
	return 0;

fail1:
	del_mc_from_global_list(mci);

fail0:
	mutex_unlock(&mem_ctls_mutex);
	return ret;
}