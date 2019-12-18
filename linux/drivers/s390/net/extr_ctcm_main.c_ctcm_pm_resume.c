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
struct ctcm_priv {TYPE_1__** channel; } ;
struct ccwgroup_device {scalar_t__ state; int /*<<< orphan*/ * cdev; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  netdev; } ;

/* Variables and functions */
 scalar_t__ CCWGROUP_OFFLINE ; 
 size_t CTCM_READ ; 
 int ccw_device_set_online (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctcm_open (int /*<<< orphan*/ ) ; 
 struct ctcm_priv* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netif_device_attach (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ctcm_pm_resume(struct ccwgroup_device *gdev)
{
	struct ctcm_priv *priv = dev_get_drvdata(&gdev->dev);
	int rc;

	if (gdev->state == CCWGROUP_OFFLINE)
		return 0;
	rc = ccw_device_set_online(gdev->cdev[1]);
	if (rc)
		goto err_out;
	rc = ccw_device_set_online(gdev->cdev[0]);
	if (rc)
		goto err_out;
	ctcm_open(priv->channel[CTCM_READ]->netdev);
err_out:
	netif_device_attach(priv->channel[CTCM_READ]->netdev);
	return rc;
}