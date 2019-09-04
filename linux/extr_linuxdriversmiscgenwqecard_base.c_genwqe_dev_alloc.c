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
struct genwqe_dev {unsigned int card_idx; int /*<<< orphan*/ * vf_jobtimeout_msec; int /*<<< orphan*/  kill_timeout; int /*<<< orphan*/  ddcb_software_timeout; int /*<<< orphan*/  print_lock; int /*<<< orphan*/  card_state; int /*<<< orphan*/  file_list; int /*<<< orphan*/  file_lock; int /*<<< orphan*/  queue_waitq; int /*<<< orphan*/  use_platform_recovery; int /*<<< orphan*/  debugfs_genwqe; int /*<<< orphan*/  class_genwqe; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_GENWQE_PLATFORM_ERROR_RECOVERY ; 
 int /*<<< orphan*/  ENODEV ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct genwqe_dev* ERR_PTR (int /*<<< orphan*/ ) ; 
 unsigned int GENWQE_CARD_NO_MAX ; 
 int /*<<< orphan*/  GENWQE_CARD_UNUSED ; 
 int /*<<< orphan*/  GENWQE_DDCB_SOFTWARE_TIMEOUT ; 
 int /*<<< orphan*/  GENWQE_KILL_TIMEOUT ; 
 unsigned int GENWQE_MAX_VFS ; 
 int /*<<< orphan*/  GENWQE_VF_JOBTIMEOUT_MSEC ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  class_genwqe ; 
 int /*<<< orphan*/  debugfs_genwqe ; 
 struct genwqe_dev** genwqe_devices ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 struct genwqe_dev* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct genwqe_dev *genwqe_dev_alloc(void)
{
	unsigned int i = 0, j;
	struct genwqe_dev *cd;

	for (i = 0; i < GENWQE_CARD_NO_MAX; i++) {
		if (genwqe_devices[i] == NULL)
			break;
	}
	if (i >= GENWQE_CARD_NO_MAX)
		return ERR_PTR(-ENODEV);

	cd = kzalloc(sizeof(struct genwqe_dev), GFP_KERNEL);
	if (!cd)
		return ERR_PTR(-ENOMEM);

	cd->card_idx = i;
	cd->class_genwqe = class_genwqe;
	cd->debugfs_genwqe = debugfs_genwqe;

	/*
	 * This comes from kernel config option and can be overritten via
	 * debugfs.
	 */
	cd->use_platform_recovery = CONFIG_GENWQE_PLATFORM_ERROR_RECOVERY;

	init_waitqueue_head(&cd->queue_waitq);

	spin_lock_init(&cd->file_lock);
	INIT_LIST_HEAD(&cd->file_list);

	cd->card_state = GENWQE_CARD_UNUSED;
	spin_lock_init(&cd->print_lock);

	cd->ddcb_software_timeout = GENWQE_DDCB_SOFTWARE_TIMEOUT;
	cd->kill_timeout = GENWQE_KILL_TIMEOUT;

	for (j = 0; j < GENWQE_MAX_VFS; j++)
		cd->vf_jobtimeout_msec[j] = GENWQE_VF_JOBTIMEOUT_MSEC;

	genwqe_devices[i] = cd;
	return cd;
}