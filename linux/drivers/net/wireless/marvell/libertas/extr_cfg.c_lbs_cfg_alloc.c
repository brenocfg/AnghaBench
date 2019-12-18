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
struct wireless_dev {int /*<<< orphan*/  wiphy; } ;
struct lbs_private {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct wireless_dev* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  kfree (struct wireless_dev*) ; 
 struct wireless_dev* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lbs_cfg80211_ops ; 
 int /*<<< orphan*/  wiphy_new (int /*<<< orphan*/ *,int) ; 

struct wireless_dev *lbs_cfg_alloc(struct device *dev)
{
	int ret = 0;
	struct wireless_dev *wdev;

	wdev = kzalloc(sizeof(struct wireless_dev), GFP_KERNEL);
	if (!wdev)
		return ERR_PTR(-ENOMEM);

	wdev->wiphy = wiphy_new(&lbs_cfg80211_ops, sizeof(struct lbs_private));
	if (!wdev->wiphy) {
		dev_err(dev, "cannot allocate wiphy\n");
		ret = -ENOMEM;
		goto err_wiphy_new;
	}

	return wdev;

 err_wiphy_new:
	kfree(wdev);
	return ERR_PTR(ret);
}