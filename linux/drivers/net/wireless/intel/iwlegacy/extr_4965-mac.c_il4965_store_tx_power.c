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
struct il_priv {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  IL_ERR (char*,int) ; 
 int /*<<< orphan*/  IL_INFO (char*,char const*) ; 
 struct il_priv* dev_get_drvdata (struct device*) ; 
 int il_set_tx_power (struct il_priv*,unsigned long,int) ; 
 int kstrtoul (char const*,int,unsigned long*) ; 

__attribute__((used)) static ssize_t
il4965_store_tx_power(struct device *d, struct device_attribute *attr,
		      const char *buf, size_t count)
{
	struct il_priv *il = dev_get_drvdata(d);
	unsigned long val;
	int ret;

	ret = kstrtoul(buf, 10, &val);
	if (ret)
		IL_INFO("%s is not in decimal form.\n", buf);
	else {
		ret = il_set_tx_power(il, val, false);
		if (ret)
			IL_ERR("failed setting tx power (0x%08x).\n", ret);
		else
			ret = count;
	}
	return ret;
}