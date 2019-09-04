#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  max_used_pages; } ;
struct zram {int /*<<< orphan*/  init_lock; int /*<<< orphan*/  mem_pool; TYPE_1__ stats; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t EINVAL ; 
 int /*<<< orphan*/  atomic_long_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct zram* dev_to_zram (struct device*) ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 scalar_t__ init_done (struct zram*) ; 
 int kstrtoul (char const*,int,unsigned long*) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zs_get_total_pages (int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t mem_used_max_store(struct device *dev,
		struct device_attribute *attr, const char *buf, size_t len)
{
	int err;
	unsigned long val;
	struct zram *zram = dev_to_zram(dev);

	err = kstrtoul(buf, 10, &val);
	if (err || val != 0)
		return -EINVAL;

	down_read(&zram->init_lock);
	if (init_done(zram)) {
		atomic_long_set(&zram->stats.max_used_pages,
				zs_get_total_pages(zram->mem_pool));
	}
	up_read(&zram->init_lock);

	return len;
}