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
struct etmv4_config {int /*<<< orphan*/  vinst_ctrl; } ;
struct etmv4_drvdata {struct etmv4_config config; } ;
struct device_attribute {int dummy; } ;
struct device {int /*<<< orphan*/  parent; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 unsigned long BMVAL (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 struct etmv4_drvdata* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scnprintf (char*,int /*<<< orphan*/ ,char*,unsigned long) ; 

__attribute__((used)) static ssize_t s_exlevel_vinst_show(struct device *dev,
				    struct device_attribute *attr,
				    char *buf)
{
	unsigned long val;
	struct etmv4_drvdata *drvdata = dev_get_drvdata(dev->parent);
	struct etmv4_config *config = &drvdata->config;

	val = BMVAL(config->vinst_ctrl, 16, 19);
	return scnprintf(buf, PAGE_SIZE, "%#lx\n", val);
}