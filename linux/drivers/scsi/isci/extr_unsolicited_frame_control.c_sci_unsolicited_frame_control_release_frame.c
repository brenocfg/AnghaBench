#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u32 ;
struct TYPE_6__ {TYPE_2__* array; } ;
struct TYPE_4__ {int /*<<< orphan*/ * array; } ;
struct sci_unsolicited_frame_control {int get; TYPE_3__ buffers; TYPE_1__ address_table; } ;
struct TYPE_5__ {scalar_t__ state; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  ENABLE_BIT ; 
 int SCU_MAX_UNSOLICITED_FRAMES ; 
 size_t SCU_UFQGP_GEN_BIT (int /*<<< orphan*/ ) ; 
 scalar_t__ UNSOLICITED_FRAME_EMPTY ; 
 scalar_t__ UNSOLICITED_FRAME_RELEASED ; 
 scalar_t__ lower_32_bits (int /*<<< orphan*/ ) ; 
 scalar_t__ upper_32_bits (int /*<<< orphan*/ ) ; 

bool sci_unsolicited_frame_control_release_frame(struct sci_unsolicited_frame_control *uf_control,
						 u32 frame_index)
{
	u32 frame_get;
	u32 frame_cycle;

	frame_get   = uf_control->get & (SCU_MAX_UNSOLICITED_FRAMES - 1);
	frame_cycle = uf_control->get & SCU_MAX_UNSOLICITED_FRAMES;

	/*
	 * In the event there are NULL entries in the UF table, we need to
	 * advance the get pointer in order to find out if this frame should
	 * be released (i.e. update the get pointer)
	 */
	while (lower_32_bits(uf_control->address_table.array[frame_get]) == 0 &&
	       upper_32_bits(uf_control->address_table.array[frame_get]) == 0 &&
	       frame_get < SCU_MAX_UNSOLICITED_FRAMES)
		frame_get++;

	/*
	 * The table has a NULL entry as it's last element.  This is
	 * illegal.
	 */
	BUG_ON(frame_get >= SCU_MAX_UNSOLICITED_FRAMES);
	if (frame_index >= SCU_MAX_UNSOLICITED_FRAMES)
		return false;

	uf_control->buffers.array[frame_index].state = UNSOLICITED_FRAME_RELEASED;

	if (frame_get != frame_index) {
		/*
		 * Frames remain in use until we advance the get pointer
		 * so there is nothing we can do here
		 */
		return false;
	}

	/*
	 * The frame index is equal to the current get pointer so we
	 * can now free up all of the frame entries that
	 */
	while (uf_control->buffers.array[frame_get].state == UNSOLICITED_FRAME_RELEASED) {
		uf_control->buffers.array[frame_get].state = UNSOLICITED_FRAME_EMPTY;

		if (frame_get+1 == SCU_MAX_UNSOLICITED_FRAMES-1) {
			frame_cycle ^= SCU_MAX_UNSOLICITED_FRAMES;
			frame_get = 0;
		} else
			frame_get++;
	}

	uf_control->get = SCU_UFQGP_GEN_BIT(ENABLE_BIT) | frame_cycle | frame_get;

	return true;
}