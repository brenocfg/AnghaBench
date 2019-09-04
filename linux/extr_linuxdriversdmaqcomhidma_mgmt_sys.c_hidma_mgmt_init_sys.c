#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct kobject {int dummy; } ;
struct hidma_mgmt_dev {int dma_channels; void** chroots; TYPE_1__* pdev; } ;
typedef  int /*<<< orphan*/  name ;
struct TYPE_7__ {struct kobject kobj; } ;
struct TYPE_6__ {int /*<<< orphan*/  mode; int /*<<< orphan*/  name; } ;
struct TYPE_5__ {TYPE_3__ dev; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (TYPE_2__*) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int S_IRUGO ; 
 int S_IWUGO ; 
 int create_sysfs_entry (struct hidma_mgmt_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int create_sysfs_entry_channel (struct hidma_mgmt_dev*,char*,int,unsigned int,void*) ; 
 void** devm_kmalloc (TYPE_3__*,int,int /*<<< orphan*/ ) ; 
 TYPE_2__* hidma_mgmt_files ; 
 void* kobject_create_and_add (char*,struct kobject*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,unsigned int) ; 

int hidma_mgmt_init_sys(struct hidma_mgmt_dev *mdev)
{
	unsigned int i;
	int rc;
	int required;
	struct kobject *chanops;

	required = sizeof(*mdev->chroots) * mdev->dma_channels;
	mdev->chroots = devm_kmalloc(&mdev->pdev->dev, required, GFP_KERNEL);
	if (!mdev->chroots)
		return -ENOMEM;

	chanops = kobject_create_and_add("chanops", &mdev->pdev->dev.kobj);
	if (!chanops)
		return -ENOMEM;

	/* create each channel directory here */
	for (i = 0; i < mdev->dma_channels; i++) {
		char name[20];

		snprintf(name, sizeof(name), "chan%d", i);
		mdev->chroots[i] = kobject_create_and_add(name, chanops);
		if (!mdev->chroots[i])
			return -ENOMEM;
	}

	/* populate common parameters */
	for (i = 0; i < ARRAY_SIZE(hidma_mgmt_files); i++) {
		rc = create_sysfs_entry(mdev, hidma_mgmt_files[i].name,
					hidma_mgmt_files[i].mode);
		if (rc)
			return rc;
	}

	/* populate parameters that are per channel */
	for (i = 0; i < mdev->dma_channels; i++) {
		rc = create_sysfs_entry_channel(mdev, "priority",
						(S_IRUGO | S_IWUGO), i,
						mdev->chroots[i]);
		if (rc)
			return rc;

		rc = create_sysfs_entry_channel(mdev, "weight",
						(S_IRUGO | S_IWUGO), i,
						mdev->chroots[i]);
		if (rc)
			return rc;
	}

	return 0;
}