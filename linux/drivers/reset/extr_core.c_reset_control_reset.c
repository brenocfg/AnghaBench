#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct reset_control {int /*<<< orphan*/  triggered_count; scalar_t__ shared; int /*<<< orphan*/  id; TYPE_2__* rcdev; int /*<<< orphan*/  acquired; int /*<<< orphan*/  deassert_count; } ;
struct TYPE_4__ {TYPE_1__* ops; } ;
struct TYPE_3__ {int (* reset ) (TYPE_2__*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int ENOTSUPP ; 
 int EPERM ; 
 int IS_ERR (struct reset_control*) ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int atomic_inc_return (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int reset_control_array_reset (int /*<<< orphan*/ ) ; 
 scalar_t__ reset_control_is_array (struct reset_control*) ; 
 int /*<<< orphan*/  rstc_to_array (struct reset_control*) ; 
 int stub1 (TYPE_2__*,int /*<<< orphan*/ ) ; 

int reset_control_reset(struct reset_control *rstc)
{
	int ret;

	if (!rstc)
		return 0;

	if (WARN_ON(IS_ERR(rstc)))
		return -EINVAL;

	if (reset_control_is_array(rstc))
		return reset_control_array_reset(rstc_to_array(rstc));

	if (!rstc->rcdev->ops->reset)
		return -ENOTSUPP;

	if (rstc->shared) {
		if (WARN_ON(atomic_read(&rstc->deassert_count) != 0))
			return -EINVAL;

		if (atomic_inc_return(&rstc->triggered_count) != 1)
			return 0;
	} else {
		if (!rstc->acquired)
			return -EPERM;
	}

	ret = rstc->rcdev->ops->reset(rstc->rcdev, rstc->id);
	if (rstc->shared && ret)
		atomic_dec(&rstc->triggered_count);

	return ret;
}