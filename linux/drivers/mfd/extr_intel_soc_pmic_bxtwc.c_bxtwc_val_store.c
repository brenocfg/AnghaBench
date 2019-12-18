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
struct intel_soc_pmic {int /*<<< orphan*/  regmap; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  bxtwc_reg_addr ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,unsigned int,int /*<<< orphan*/ ) ; 
 struct intel_soc_pmic* dev_get_drvdata (struct device*) ; 
 int kstrtouint (char const*,int /*<<< orphan*/ ,unsigned int*) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static ssize_t bxtwc_val_store(struct device *dev,
	struct device_attribute *attr, const char *buf, size_t count)
{
	int ret;
	unsigned int val;
	struct intel_soc_pmic *pmic = dev_get_drvdata(dev);

	ret = kstrtouint(buf, 0, &val);
	if (ret)
		return ret;

	ret = regmap_write(pmic->regmap, bxtwc_reg_addr, val);
	if (ret) {
		dev_err(dev, "Failed to write value 0x%02x to address 0x%lx",
			val, bxtwc_reg_addr);
		return -EIO;
	}
	return count;
}