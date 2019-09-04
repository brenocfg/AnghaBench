#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  channel; } ;
struct intel_guc_log {TYPE_4__ relay; TYPE_3__* vma; } ;
struct TYPE_7__ {TYPE_2__* obj; } ;
struct TYPE_5__ {int /*<<< orphan*/  size; } ;
struct TYPE_6__ {TYPE_1__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  relay_flush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  relay_reserve (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_wmb () ; 

__attribute__((used)) static void guc_move_to_next_buf(struct intel_guc_log *log)
{
	/*
	 * Make sure the updates made in the sub buffer are visible when
	 * Consumer sees the following update to offset inside the sub buffer.
	 */
	smp_wmb();

	/* All data has been written, so now move the offset of sub buffer. */
	relay_reserve(log->relay.channel, log->vma->obj->base.size);

	/* Switch to the next sub buffer */
	relay_flush(log->relay.channel);
}