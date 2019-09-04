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
struct dm_target {int dummy; } ;
struct dm_dev {struct dax_device* dax_dev; } ;
struct dax_device {int dummy; } ;
typedef  int /*<<< orphan*/  sector_t ;

/* Variables and functions */
 scalar_t__ dax_write_cache_enabled (struct dax_device*) ; 

__attribute__((used)) static int device_dax_write_cache_enabled(struct dm_target *ti,
					  struct dm_dev *dev, sector_t start,
					  sector_t len, void *data)
{
	struct dax_device *dax_dev = dev->dax_dev;

	if (!dax_dev)
		return false;

	if (dax_write_cache_enabled(dax_dev))
		return true;
	return false;
}