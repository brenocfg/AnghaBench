#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct reset_control {int /*<<< orphan*/  id; TYPE_2__* rcdev; int /*<<< orphan*/  acquired; int /*<<< orphan*/  deassert_count; int /*<<< orphan*/  triggered_count; scalar_t__ shared; } ;
struct TYPE_5__ {TYPE_1__* ops; } ;
struct TYPE_4__ {int (* deassert ) (TYPE_2__*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int EPERM ; 
 int IS_ERR (struct reset_control*) ; 
 int /*<<< orphan*/  WARN (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ WARN_ON (int) ; 
 int atomic_inc_return (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcdev_name (TYPE_2__*) ; 
 int reset_control_array_deassert (int /*<<< orphan*/ ) ; 
 scalar_t__ reset_control_is_array (struct reset_control*) ; 
 int /*<<< orphan*/  rstc_to_array (struct reset_control*) ; 
 int stub1 (TYPE_2__*,int /*<<< orphan*/ ) ; 

int reset_control_deassert(struct reset_control *rstc)
{
	if (!rstc)
		return 0;

	if (WARN_ON(IS_ERR(rstc)))
		return -EINVAL;

	if (reset_control_is_array(rstc))
		return reset_control_array_deassert(rstc_to_array(rstc));

	if (rstc->shared) {
		if (WARN_ON(atomic_read(&rstc->triggered_count) != 0))
			return -EINVAL;

		if (atomic_inc_return(&rstc->deassert_count) != 1)
			return 0;
	} else {
		if (!rstc->acquired) {
			WARN(1, "reset %s (ID: %u) is not acquired\n",
			     rcdev_name(rstc->rcdev), rstc->id);
			return -EPERM;
		}
	}

	/*
	 * If the reset controller does not implement .deassert(), we assume
	 * that it handles self-deasserting reset lines via .reset(). In that
	 * case, the reset lines are deasserted by default. If that is not the
	 * case, the reset controller driver should implement .deassert() and
	 * return -ENOTSUPP.
	 */
	if (!rstc->rcdev->ops->deassert)
		return 0;

	return rstc->rcdev->ops->deassert(rstc->rcdev, rstc->id);
}