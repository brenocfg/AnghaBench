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
struct venus_inst {TYPE_1__* tss; } ;
struct vb2_buffer {int /*<<< orphan*/  timestamp; } ;
struct vb2_v4l2_buffer {int /*<<< orphan*/  timecode; int /*<<< orphan*/  flags; struct vb2_buffer vb2_buf; } ;
struct TYPE_2__ {int used; scalar_t__ ts_us; int /*<<< orphan*/  ts_ns; int /*<<< orphan*/  tc; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (TYPE_1__*) ; 

void venus_helper_get_ts_metadata(struct venus_inst *inst, u64 timestamp_us,
				  struct vb2_v4l2_buffer *vbuf)
{
	struct vb2_buffer *vb = &vbuf->vb2_buf;
	unsigned int i;

	for (i = 0; i < ARRAY_SIZE(inst->tss); ++i) {
		if (!inst->tss[i].used)
			continue;

		if (inst->tss[i].ts_us != timestamp_us)
			continue;

		inst->tss[i].used = false;
		vbuf->flags |= inst->tss[i].flags;
		vbuf->timecode = inst->tss[i].tc;
		vb->timestamp = inst->tss[i].ts_ns;
		break;
	}
}