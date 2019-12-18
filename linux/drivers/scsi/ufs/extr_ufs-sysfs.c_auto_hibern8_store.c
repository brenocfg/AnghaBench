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
struct ufs_hba {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t EINVAL ; 
 size_t EOPNOTSUPP ; 
 unsigned int UFSHCI_AHIBERN8_MAX ; 
 struct ufs_hba* dev_get_drvdata (struct device*) ; 
 scalar_t__ kstrtouint (char const*,int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  ufshcd_auto_hibern8_update (struct ufs_hba*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ufshcd_is_auto_hibern8_supported (struct ufs_hba*) ; 
 int /*<<< orphan*/  ufshcd_us_to_ahit (unsigned int) ; 

__attribute__((used)) static ssize_t auto_hibern8_store(struct device *dev,
				  struct device_attribute *attr,
				  const char *buf, size_t count)
{
	struct ufs_hba *hba = dev_get_drvdata(dev);
	unsigned int timer;

	if (!ufshcd_is_auto_hibern8_supported(hba))
		return -EOPNOTSUPP;

	if (kstrtouint(buf, 0, &timer))
		return -EINVAL;

	if (timer > UFSHCI_AHIBERN8_MAX)
		return -EINVAL;

	ufshcd_auto_hibern8_update(hba, ufshcd_us_to_ahit(timer));

	return count;
}