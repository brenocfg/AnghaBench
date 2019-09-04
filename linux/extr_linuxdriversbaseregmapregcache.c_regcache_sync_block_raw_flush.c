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
struct TYPE_2__ {size_t val_bytes; } ;
struct regmap {unsigned int reg_stride; int cache_bypass; int /*<<< orphan*/  dev; TYPE_1__ format; } ;

/* Variables and functions */
 int _regmap_raw_write (struct regmap*,unsigned int,void const*,int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,unsigned int,unsigned int,int) ; 

__attribute__((used)) static int regcache_sync_block_raw_flush(struct regmap *map, const void **data,
					 unsigned int base, unsigned int cur)
{
	size_t val_bytes = map->format.val_bytes;
	int ret, count;

	if (*data == NULL)
		return 0;

	count = (cur - base) / map->reg_stride;

	dev_dbg(map->dev, "Writing %zu bytes for %d registers from 0x%x-0x%x\n",
		count * val_bytes, count, base, cur - map->reg_stride);

	map->cache_bypass = true;

	ret = _regmap_raw_write(map, base, *data, count * val_bytes);
	if (ret)
		dev_err(map->dev, "Unable to sync registers %#x-%#x. %d\n",
			base, cur - map->reg_stride, ret);

	map->cache_bypass = false;

	*data = NULL;

	return ret;
}