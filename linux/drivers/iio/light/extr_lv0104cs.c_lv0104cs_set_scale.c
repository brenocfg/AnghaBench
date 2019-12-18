#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct lv0104cs_private {int scale; int /*<<< orphan*/  lock; } ;
struct TYPE_3__ {int val; int val2; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int EINVAL ; 
 TYPE_1__* lv0104cs_scales ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int lv0104cs_set_scale(struct lv0104cs_private *lv0104cs,
				int val, int val2)
{
	int i;

	/* hard matching */
	for (i = 0; i < ARRAY_SIZE(lv0104cs_scales); i++) {
		if (val != lv0104cs_scales[i].val)
			continue;

		if (val2 == lv0104cs_scales[i].val2)
			break;
	}

	if (i == ARRAY_SIZE(lv0104cs_scales))
		return -EINVAL;

	mutex_lock(&lv0104cs->lock);
	lv0104cs->scale = i;
	mutex_unlock(&lv0104cs->lock);

	return 0;
}