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
struct ctcm_priv {int /*<<< orphan*/  protocol; } ;
struct ccwgroup_device {scalar_t__ state; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ CCWGROUP_ONLINE ; 
 int /*<<< orphan*/  CTCM_DBF_TEXT_ (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct ccwgroup_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CTC_DBF_INFO ; 
 int /*<<< orphan*/  SETUP ; 
 int /*<<< orphan*/  ctcm_shutdown_device (struct ccwgroup_device*) ; 
 struct ctcm_priv* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_set_drvdata (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct ctcm_priv*) ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ctcm_remove_device(struct ccwgroup_device *cgdev)
{
	struct ctcm_priv *priv = dev_get_drvdata(&cgdev->dev);

	CTCM_DBF_TEXT_(SETUP, CTC_DBF_INFO,
			"removing device %p, proto : %d",
			cgdev, priv->protocol);

	if (cgdev->state == CCWGROUP_ONLINE)
		ctcm_shutdown_device(cgdev);
	dev_set_drvdata(&cgdev->dev, NULL);
	kfree(priv);
	put_device(&cgdev->dev);
}