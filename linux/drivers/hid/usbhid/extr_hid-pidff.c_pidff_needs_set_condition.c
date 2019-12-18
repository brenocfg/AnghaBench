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
struct TYPE_2__ {struct ff_condition_effect* condition; } ;
struct ff_effect {TYPE_1__ u; } ;
struct ff_condition_effect {scalar_t__ center; scalar_t__ right_coeff; scalar_t__ left_coeff; scalar_t__ right_saturation; scalar_t__ left_saturation; scalar_t__ deadband; } ;

/* Variables and functions */

__attribute__((used)) static int pidff_needs_set_condition(struct ff_effect *effect,
				     struct ff_effect *old)
{
	int i;
	int ret = 0;

	for (i = 0; i < 2; i++) {
		struct ff_condition_effect *cond = &effect->u.condition[i];
		struct ff_condition_effect *old_cond = &old->u.condition[i];

		ret |= cond->center != old_cond->center ||
		       cond->right_coeff != old_cond->right_coeff ||
		       cond->left_coeff != old_cond->left_coeff ||
		       cond->right_saturation != old_cond->right_saturation ||
		       cond->left_saturation != old_cond->left_saturation ||
		       cond->deadband != old_cond->deadband;
	}

	return ret;
}