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
struct regmap {int async; int /*<<< orphan*/  lock_arg; int /*<<< orphan*/  (* unlock ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* lock ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  reg_stride; TYPE_1__ format; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  IS_ALIGNED (unsigned int,int /*<<< orphan*/ ) ; 
 int _regmap_raw_write (struct regmap*,unsigned int,void const*,size_t) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ) ; 

int regmap_raw_write_async(struct regmap *map, unsigned int reg,
			   const void *val, size_t val_len)
{
	int ret;

	if (val_len % map->format.val_bytes)
		return -EINVAL;
	if (!IS_ALIGNED(reg, map->reg_stride))
		return -EINVAL;

	map->lock(map->lock_arg);

	map->async = true;

	ret = _regmap_raw_write(map, reg, val, val_len);

	map->async = false;

	map->unlock(map->lock_arg);

	return ret;
}