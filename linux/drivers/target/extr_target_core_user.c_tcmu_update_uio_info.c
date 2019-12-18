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
struct uio_info {char* name; } ;
struct tcmu_hba {int /*<<< orphan*/  host_id; } ;
struct tcmu_dev {int /*<<< orphan*/  name; scalar_t__* dev_config; struct uio_info uio_info; TYPE_1__* hba; } ;
struct TYPE_2__ {struct tcmu_hba* hba_ptr; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 char* kasprintf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  kfree (char*) ; 

__attribute__((used)) static int tcmu_update_uio_info(struct tcmu_dev *udev)
{
	struct tcmu_hba *hba = udev->hba->hba_ptr;
	struct uio_info *info;
	char *str;

	info = &udev->uio_info;

	if (udev->dev_config[0])
		str = kasprintf(GFP_KERNEL, "tcm-user/%u/%s/%s", hba->host_id,
				udev->name, udev->dev_config);
	else
		str = kasprintf(GFP_KERNEL, "tcm-user/%u/%s", hba->host_id,
				udev->name);
	if (!str)
		return -ENOMEM;

	/* If the old string exists, free it */
	kfree(info->name);
	info->name = str;

	return 0;
}