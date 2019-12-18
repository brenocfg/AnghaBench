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
struct vc4_exec_info {int /*<<< orphan*/  head; } ;
struct vc4_dev {int /*<<< orphan*/  render_job_list; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_move_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct vc4_dev* to_vc4_dev (struct drm_device*) ; 
 int /*<<< orphan*/  vc4_submit_next_render_job (struct drm_device*) ; 

void
vc4_move_job_to_render(struct drm_device *dev, struct vc4_exec_info *exec)
{
	struct vc4_dev *vc4 = to_vc4_dev(dev);
	bool was_empty = list_empty(&vc4->render_job_list);

	list_move_tail(&exec->head, &vc4->render_job_list);
	if (was_empty)
		vc4_submit_next_render_job(dev);
}