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
struct regmap {int patch_regs; int cache_bypass; int async; int /*<<< orphan*/  lock_arg; int /*<<< orphan*/  (* unlock ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* lock ) (int /*<<< orphan*/ ) ;struct reg_sequence* patch; } ;
struct reg_sequence {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ WARN_ONCE (int,char*,int) ; 
 int _regmap_multi_reg_write (struct regmap*,struct reg_sequence const*,int) ; 
 struct reg_sequence* krealloc (struct reg_sequence*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct reg_sequence*,struct reg_sequence const*,int) ; 
 int /*<<< orphan*/  regmap_async_complete (struct regmap*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ) ; 

int regmap_register_patch(struct regmap *map, const struct reg_sequence *regs,
			  int num_regs)
{
	struct reg_sequence *p;
	int ret;
	bool bypass;

	if (WARN_ONCE(num_regs <= 0, "invalid registers number (%d)\n",
	    num_regs))
		return 0;

	p = krealloc(map->patch,
		     sizeof(struct reg_sequence) * (map->patch_regs + num_regs),
		     GFP_KERNEL);
	if (p) {
		memcpy(p + map->patch_regs, regs, num_regs * sizeof(*regs));
		map->patch = p;
		map->patch_regs += num_regs;
	} else {
		return -ENOMEM;
	}

	map->lock(map->lock_arg);

	bypass = map->cache_bypass;

	map->cache_bypass = true;
	map->async = true;

	ret = _regmap_multi_reg_write(map, regs, num_regs);

	map->async = false;
	map->cache_bypass = bypass;

	map->unlock(map->lock_arg);

	regmap_async_complete(map);

	return ret;
}