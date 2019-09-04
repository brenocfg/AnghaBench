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
struct fsi_master_acf {scalar_t__ external_mode; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 scalar_t__ PAGE_SIZE ; 
 struct fsi_master_acf* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  snprintf (char*,scalar_t__,char*,int) ; 

__attribute__((used)) static ssize_t external_mode_show(struct device *dev,
				  struct device_attribute *attr, char *buf)
{
	struct fsi_master_acf *master = dev_get_drvdata(dev);

	return snprintf(buf, PAGE_SIZE - 1, "%u\n",
			master->external_mode ? 1 : 0);
}