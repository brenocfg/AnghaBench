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
struct wireless_dev {scalar_t__ wiphy; } ;
struct lbs_private {scalar_t__ wiphy_registered; struct wireless_dev* wdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct wireless_dev*) ; 
 int /*<<< orphan*/  wiphy_free (scalar_t__) ; 
 int /*<<< orphan*/  wiphy_unregister (scalar_t__) ; 

void lbs_cfg_free(struct lbs_private *priv)
{
	struct wireless_dev *wdev = priv->wdev;

	if (!wdev)
		return;

	if (priv->wiphy_registered)
		wiphy_unregister(wdev->wiphy);

	if (wdev->wiphy)
		wiphy_free(wdev->wiphy);

	kfree(wdev);
}