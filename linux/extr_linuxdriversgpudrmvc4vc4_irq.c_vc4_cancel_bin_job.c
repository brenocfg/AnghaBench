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
struct vc4_exec_info {int /*<<< orphan*/  head; scalar_t__ perfmon; } ;
struct vc4_dev {int /*<<< orphan*/  bin_job_list; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_move_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct vc4_dev* to_vc4_dev (struct drm_device*) ; 
 struct vc4_exec_info* vc4_first_bin_job (struct vc4_dev*) ; 
 int /*<<< orphan*/  vc4_perfmon_stop (struct vc4_dev*,scalar_t__,int) ; 
 int /*<<< orphan*/  vc4_submit_next_bin_job (struct drm_device*) ; 

__attribute__((used)) static void
vc4_cancel_bin_job(struct drm_device *dev)
{
	struct vc4_dev *vc4 = to_vc4_dev(dev);
	struct vc4_exec_info *exec = vc4_first_bin_job(vc4);

	if (!exec)
		return;

	/* Stop the perfmon so that the next bin job can be started. */
	if (exec->perfmon)
		vc4_perfmon_stop(vc4, exec->perfmon, false);

	list_move_tail(&exec->head, &vc4->bin_job_list);
	vc4_submit_next_bin_job(dev);
}