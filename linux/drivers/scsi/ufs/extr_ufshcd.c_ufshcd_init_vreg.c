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
struct ufs_vreg_info {int /*<<< orphan*/  vccq2; int /*<<< orphan*/  vccq; int /*<<< orphan*/  vcc; } ;
struct ufs_hba {struct ufs_vreg_info vreg_info; struct device* dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ufshcd_get_vreg (struct device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ufshcd_init_vreg(struct ufs_hba *hba)
{
	int ret = 0;
	struct device *dev = hba->dev;
	struct ufs_vreg_info *info = &hba->vreg_info;

	ret = ufshcd_get_vreg(dev, info->vcc);
	if (ret)
		goto out;

	ret = ufshcd_get_vreg(dev, info->vccq);
	if (ret)
		goto out;

	ret = ufshcd_get_vreg(dev, info->vccq2);
out:
	return ret;
}