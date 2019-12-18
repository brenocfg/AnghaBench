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
struct TYPE_3__ {int /*<<< orphan*/  weight; } ;
struct vgpu_sched_data {int /*<<< orphan*/  lru_list; struct intel_vgpu* vgpu; TYPE_1__ sched_ctl; } ;
struct TYPE_4__ {int /*<<< orphan*/  weight; } ;
struct intel_vgpu {struct vgpu_sched_data* sched_data; TYPE_2__ sched_ctl; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 struct vgpu_sched_data* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tbs_sched_init_vgpu(struct intel_vgpu *vgpu)
{
	struct vgpu_sched_data *data;

	data = kzalloc(sizeof(*data), GFP_KERNEL);
	if (!data)
		return -ENOMEM;

	data->sched_ctl.weight = vgpu->sched_ctl.weight;
	data->vgpu = vgpu;
	INIT_LIST_HEAD(&data->lru_list);

	vgpu->sched_data = data;

	return 0;
}