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
struct ufs_hba {int /*<<< orphan*/  ahit; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  EOPNOTSUPP ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 struct ufs_hba* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,int) ; 
 int ufshcd_ahit_to_us (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ufshcd_is_auto_hibern8_supported (struct ufs_hba*) ; 

__attribute__((used)) static ssize_t auto_hibern8_show(struct device *dev,
				 struct device_attribute *attr, char *buf)
{
	struct ufs_hba *hba = dev_get_drvdata(dev);

	if (!ufshcd_is_auto_hibern8_supported(hba))
		return -EOPNOTSUPP;

	return snprintf(buf, PAGE_SIZE, "%d\n", ufshcd_ahit_to_us(hba->ahit));
}