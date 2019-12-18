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
struct vgpu_sched_data {int active; int /*<<< orphan*/  lru_list; } ;
struct intel_vgpu {struct vgpu_sched_data* sched_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void tbs_sched_stop_schedule(struct intel_vgpu *vgpu)
{
	struct vgpu_sched_data *vgpu_data = vgpu->sched_data;

	list_del_init(&vgpu_data->lru_list);
	vgpu_data->active = false;
}