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
struct qed_dev {int /*<<< orphan*/  dl; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devlink_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devlink_params_unregister (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devlink_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qed_devlink_params ; 

__attribute__((used)) static void qed_devlink_unregister(struct qed_dev *cdev)
{
	if (!cdev->dl)
		return;

	devlink_params_unregister(cdev->dl, qed_devlink_params,
				  ARRAY_SIZE(qed_devlink_params));

	devlink_unregister(cdev->dl);
	devlink_free(cdev->dl);
}