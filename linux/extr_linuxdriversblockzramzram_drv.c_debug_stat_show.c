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
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_2__ {int /*<<< orphan*/  miss_free; int /*<<< orphan*/  writestall; } ;
struct zram {int /*<<< orphan*/  init_lock; TYPE_1__ stats; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 scalar_t__ atomic64_read (int /*<<< orphan*/ *) ; 
 struct zram* dev_to_zram (struct device*) ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scnprintf (char*,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t debug_stat_show(struct device *dev,
		struct device_attribute *attr, char *buf)
{
	int version = 1;
	struct zram *zram = dev_to_zram(dev);
	ssize_t ret;

	down_read(&zram->init_lock);
	ret = scnprintf(buf, PAGE_SIZE,
			"version: %d\n%8llu %8llu\n",
			version,
			(u64)atomic64_read(&zram->stats.writestall),
			(u64)atomic64_read(&zram->stats.miss_free));
	up_read(&zram->init_lock);

	return ret;
}