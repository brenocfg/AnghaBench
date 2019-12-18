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
typedef  scalar_t__ u64 ;
struct region {scalar_t__ max; scalar_t__ min; int /*<<< orphan*/  bit; } ;
struct aspeed_p2a_user {int* readwrite; } ;
struct aspeed_p2a_ctrl_mapping {scalar_t__ addr; int length; } ;
struct aspeed_p2a_ctrl {int* readerwriters; int /*<<< orphan*/  regmap; int /*<<< orphan*/  tracking; TYPE_1__* config; } ;
struct TYPE_2__ {struct region* regions; } ;

/* Variables and functions */
 int P2A_REGION_COUNT ; 
 int /*<<< orphan*/  SCU2C ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool aspeed_p2a_region_acquire(struct aspeed_p2a_user *priv,
		struct aspeed_p2a_ctrl *ctrl,
		struct aspeed_p2a_ctrl_mapping *map)
{
	int i;
	u64 base, end;
	bool matched = false;

	base = map->addr;
	end = map->addr + (map->length - 1);

	/* If the value is a legal u32, it will find a match. */
	for (i = 0; i < P2A_REGION_COUNT; i++) {
		const struct region *curr = &ctrl->config->regions[i];

		/* If the top of this region is lower than your base, skip it.
		 */
		if (curr->max < base)
			continue;

		/* If the bottom of this region is higher than your end, bail.
		 */
		if (curr->min > end)
			break;

		/* Lock this and update it, therefore it someone else is
		 * closing their file out, this'll preserve the increment.
		 */
		mutex_lock(&ctrl->tracking);
		ctrl->readerwriters[i] += 1;
		mutex_unlock(&ctrl->tracking);

		/* Track with the user, so when they close their file, we can
		 * decrement properly.
		 */
		priv->readwrite[i] += 1;

		/* Enable the region as read-write. */
		regmap_update_bits(ctrl->regmap, SCU2C, curr->bit, 0);
		matched = true;
	}

	return matched;
}