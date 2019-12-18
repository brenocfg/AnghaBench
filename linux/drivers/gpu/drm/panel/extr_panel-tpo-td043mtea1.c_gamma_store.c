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
struct td043mtea1_panel {unsigned int* gamma; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t EINVAL ; 
 struct td043mtea1_panel* dev_get_drvdata (struct device*) ; 
 int sscanf (char const*,char*,unsigned int*,unsigned int*,unsigned int*,unsigned int*,unsigned int*,unsigned int*,unsigned int*,unsigned int*,unsigned int*,unsigned int*,unsigned int*,unsigned int*) ; 
 int /*<<< orphan*/  td043mtea1_write_gamma (struct td043mtea1_panel*) ; 

__attribute__((used)) static ssize_t gamma_store(struct device *dev, struct device_attribute *attr,
			   const char *buf, size_t count)
{
	struct td043mtea1_panel *lcd = dev_get_drvdata(dev);
	unsigned int g[12];
	unsigned int i;
	int ret;

	ret = sscanf(buf, "%u %u %u %u %u %u %u %u %u %u %u %u",
		     &g[0], &g[1], &g[2], &g[3], &g[4], &g[5],
		     &g[6], &g[7], &g[8], &g[9], &g[10], &g[11]);
	if (ret != 12)
		return -EINVAL;

	for (i = 0; i < 12; i++)
		lcd->gamma[i] = g[i];

	td043mtea1_write_gamma(lcd);

	return count;
}