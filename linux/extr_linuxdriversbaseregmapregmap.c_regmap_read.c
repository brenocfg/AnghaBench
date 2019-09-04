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
struct regmap {int /*<<< orphan*/  lock_arg; int /*<<< orphan*/  (* unlock ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* lock ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  reg_stride; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  IS_ALIGNED (unsigned int,int /*<<< orphan*/ ) ; 
 int _regmap_read (struct regmap*,unsigned int,unsigned int*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ) ; 

int regmap_read(struct regmap *map, unsigned int reg, unsigned int *val)
{
	int ret;

	if (!IS_ALIGNED(reg, map->reg_stride))
		return -EINVAL;

	map->lock(map->lock_arg);

	ret = _regmap_read(map, reg, val);

	map->unlock(map->lock_arg);

	return ret;
}