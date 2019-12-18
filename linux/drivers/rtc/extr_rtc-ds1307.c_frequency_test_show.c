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
struct ds1307 {int /*<<< orphan*/  regmap; } ;
struct device_attribute {int dummy; } ;
struct device {int /*<<< orphan*/  parent; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 unsigned int M41TXX_BIT_FT ; 
 int /*<<< orphan*/  M41TXX_REG_CONTROL ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 struct ds1307* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  scnprintf (char*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static ssize_t frequency_test_show(struct device *dev,
				   struct device_attribute *attr,
				   char *buf)
{
	struct ds1307 *ds1307 = dev_get_drvdata(dev->parent);
	unsigned int ctrl_reg;

	regmap_read(ds1307->regmap, M41TXX_REG_CONTROL, &ctrl_reg);

	return scnprintf(buf, PAGE_SIZE, (ctrl_reg & M41TXX_BIT_FT) ? "on\n" :
			"off\n");
}