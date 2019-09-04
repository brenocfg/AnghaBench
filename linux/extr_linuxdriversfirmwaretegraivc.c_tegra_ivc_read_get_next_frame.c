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
struct TYPE_2__ {int /*<<< orphan*/  position; int /*<<< orphan*/  channel; int /*<<< orphan*/  phys; } ;
struct tegra_ivc {TYPE_1__ rx; int /*<<< orphan*/  frame_size; } ;

/* Variables and functions */
 int EINVAL ; 
 void* ERR_PTR (int) ; 
 scalar_t__ WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_rmb () ; 
 int tegra_ivc_check_read (struct tegra_ivc*) ; 
 void* tegra_ivc_frame_virt (struct tegra_ivc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tegra_ivc_invalidate_frame (struct tegra_ivc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void *tegra_ivc_read_get_next_frame(struct tegra_ivc *ivc)
{
	int err;

	if (WARN_ON(ivc == NULL))
		return ERR_PTR(-EINVAL);

	err = tegra_ivc_check_read(ivc);
	if (err < 0)
		return ERR_PTR(err);

	/*
	 * Order observation of ivc->rx.position potentially indicating new
	 * data before data read.
	 */
	smp_rmb();

	tegra_ivc_invalidate_frame(ivc, ivc->rx.phys, ivc->rx.position, 0,
				   ivc->frame_size);

	return tegra_ivc_frame_virt(ivc, ivc->rx.channel, ivc->rx.position);
}