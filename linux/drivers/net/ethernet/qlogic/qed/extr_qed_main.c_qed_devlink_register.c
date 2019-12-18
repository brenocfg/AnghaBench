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
union devlink_param_value {int vbool; } ;
struct qed_devlink {struct qed_dev* cdev; } ;
struct qed_dev {int iwarp_cmt; struct devlink* dl; TYPE_1__* pdev; } ;
struct devlink {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  QED_DEVLINK_PARAM_ID_IWARP_CMT ; 
 struct devlink* devlink_alloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  devlink_free (struct devlink*) ; 
 int /*<<< orphan*/  devlink_param_driverinit_value_set (struct devlink*,int /*<<< orphan*/ ,union devlink_param_value) ; 
 int /*<<< orphan*/  devlink_params_publish (struct devlink*) ; 
 int devlink_params_register (struct devlink*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct qed_devlink* devlink_priv (struct devlink*) ; 
 int devlink_register (struct devlink*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devlink_unregister (struct devlink*) ; 
 int /*<<< orphan*/  qed_devlink_params ; 
 int /*<<< orphan*/  qed_dl_ops ; 

__attribute__((used)) static int qed_devlink_register(struct qed_dev *cdev)
{
	union devlink_param_value value;
	struct qed_devlink *qed_dl;
	struct devlink *dl;
	int rc;

	dl = devlink_alloc(&qed_dl_ops, sizeof(*qed_dl));
	if (!dl)
		return -ENOMEM;

	qed_dl = devlink_priv(dl);

	cdev->dl = dl;
	qed_dl->cdev = cdev;

	rc = devlink_register(dl, &cdev->pdev->dev);
	if (rc)
		goto err_free;

	rc = devlink_params_register(dl, qed_devlink_params,
				     ARRAY_SIZE(qed_devlink_params));
	if (rc)
		goto err_unregister;

	value.vbool = false;
	devlink_param_driverinit_value_set(dl,
					   QED_DEVLINK_PARAM_ID_IWARP_CMT,
					   value);

	devlink_params_publish(dl);
	cdev->iwarp_cmt = false;

	return 0;

err_unregister:
	devlink_unregister(dl);

err_free:
	cdev->dl = NULL;
	devlink_free(dl);

	return rc;
}