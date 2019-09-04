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
struct mmc_blk_data {scalar_t__ read_only; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dev_to_disk (struct device*) ; 
 struct mmc_blk_data* mmc_blk_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmc_blk_put (struct mmc_blk_data*) ; 
 int /*<<< orphan*/  set_disk_ro (int /*<<< orphan*/ ,int) ; 
 unsigned long simple_strtoul (char const*,char**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t force_ro_store(struct device *dev, struct device_attribute *attr,
			      const char *buf, size_t count)
{
	int ret;
	char *end;
	struct mmc_blk_data *md = mmc_blk_get(dev_to_disk(dev));
	unsigned long set = simple_strtoul(buf, &end, 0);
	if (end == buf) {
		ret = -EINVAL;
		goto out;
	}

	set_disk_ro(dev_to_disk(dev), set || md->read_only);
	ret = count;
out:
	mmc_blk_put(md);
	return ret;
}