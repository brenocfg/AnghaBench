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
struct net_device {int dummy; } ;
struct bnxt_re_dev {int dummy; } ;
struct bnxt_en_dev {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 struct bnxt_en_dev* ERR_PTR (int) ; 
 scalar_t__ IS_ERR (struct bnxt_en_dev*) ; 
 int PTR_ERR (struct bnxt_en_dev*) ; 
 int /*<<< orphan*/  ROCE_DRV_MODULE_NAME ; 
 struct bnxt_re_dev* bnxt_re_dev_add (struct net_device*,struct bnxt_en_dev*) ; 
 struct bnxt_en_dev* bnxt_re_dev_probe (struct net_device*) ; 
 int /*<<< orphan*/  bnxt_re_dev_unprobe (struct net_device*,struct bnxt_en_dev*) ; 
 int /*<<< orphan*/  is_bnxt_re_dev (struct net_device*) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bnxt_re_dev_reg(struct bnxt_re_dev **rdev, struct net_device *netdev)
{
	struct bnxt_en_dev *en_dev;
	int rc = 0;

	if (!is_bnxt_re_dev(netdev))
		return -ENODEV;

	en_dev = bnxt_re_dev_probe(netdev);
	if (IS_ERR(en_dev)) {
		if (en_dev != ERR_PTR(-ENODEV))
			pr_err("%s: Failed to probe\n", ROCE_DRV_MODULE_NAME);
		rc = PTR_ERR(en_dev);
		goto exit;
	}
	*rdev = bnxt_re_dev_add(netdev, en_dev);
	if (!*rdev) {
		rc = -ENOMEM;
		bnxt_re_dev_unprobe(netdev, en_dev);
		goto exit;
	}
exit:
	return rc;
}