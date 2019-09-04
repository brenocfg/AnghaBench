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
struct fmc_device {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {struct fc_instance* name; int /*<<< orphan*/ * fops; int /*<<< orphan*/  minor; } ;
struct fc_instance {TYPE_1__ misc; struct fmc_device* fmc; int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MISC_DYNAMIC_MINOR ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,struct fc_instance*) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fc_devices ; 
 int /*<<< orphan*/  fc_drv ; 
 int /*<<< orphan*/  fc_fops ; 
 int /*<<< orphan*/  fc_lock ; 
 int fmc_validate (struct fmc_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct fc_instance*) ; 
 struct fc_instance* kstrdup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct fc_instance* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int misc_register (TYPE_1__*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int fc_probe(struct fmc_device *fmc)
{
	int ret;
	int index = 0;

	struct fc_instance *fc;

	index = fmc_validate(fmc, &fc_drv);
	if (index < 0)
		return -EINVAL; /* not our device: invalid */

	/* Create a char device: we want to create it anew */
	fc = kzalloc(sizeof(*fc), GFP_KERNEL);
	if (!fc)
		return -ENOMEM;
	fc->fmc = fmc;
	fc->misc.minor = MISC_DYNAMIC_MINOR;
	fc->misc.fops = &fc_fops;
	fc->misc.name = kstrdup(dev_name(&fmc->dev), GFP_KERNEL);

	ret = misc_register(&fc->misc);
	if (ret < 0)
		goto out;
	spin_lock(&fc_lock);
	list_add(&fc->list, &fc_devices);
	spin_unlock(&fc_lock);
	dev_info(&fc->fmc->dev, "Created misc device \"%s\"\n",
		 fc->misc.name);
	return 0;

out:
	kfree(fc->misc.name);
	kfree(fc);
	return ret;
}