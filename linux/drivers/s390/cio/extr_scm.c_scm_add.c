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
struct scm_device {int /*<<< orphan*/  dev; } ;
struct sale {int dummy; } ;
struct chsc_scm_info {int /*<<< orphan*/  mbc; int /*<<< orphan*/  is; struct sale* scmal; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int device_register (int /*<<< orphan*/ *) ; 
 struct scm_device* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ *) ; 
 struct scm_device* scmdev_find (struct sale*) ; 
 int /*<<< orphan*/  scmdev_setup (struct scm_device*,struct sale*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scmdev_update (struct scm_device*,struct sale*) ; 

__attribute__((used)) static int scm_add(struct chsc_scm_info *scm_info, size_t num)
{
	struct sale *sale, *scmal = scm_info->scmal;
	struct scm_device *scmdev;
	int ret;

	for (sale = scmal; sale < scmal + num; sale++) {
		scmdev = scmdev_find(sale);
		if (scmdev) {
			scmdev_update(scmdev, sale);
			/* Release reference from scm_find(). */
			put_device(&scmdev->dev);
			continue;
		}
		scmdev = kzalloc(sizeof(*scmdev), GFP_KERNEL);
		if (!scmdev)
			return -ENODEV;
		scmdev_setup(scmdev, sale, scm_info->is, scm_info->mbc);
		ret = device_register(&scmdev->dev);
		if (ret) {
			/* Release reference from device_initialize(). */
			put_device(&scmdev->dev);
			return ret;
		}
	}

	return 0;
}