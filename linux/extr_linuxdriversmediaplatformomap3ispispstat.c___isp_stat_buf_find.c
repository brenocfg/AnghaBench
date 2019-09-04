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
struct ispstat_buffer {scalar_t__ frame_number; scalar_t__ empty; } ;
struct ispstat {struct ispstat_buffer* active_buf; struct ispstat_buffer* locked_buf; struct ispstat_buffer* buf; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int STAT_MAX_BUFS ; 

__attribute__((used)) static struct ispstat_buffer *
__isp_stat_buf_find(struct ispstat *stat, int look_empty)
{
	struct ispstat_buffer *found = NULL;
	int i;

	for (i = 0; i < STAT_MAX_BUFS; i++) {
		struct ispstat_buffer *curr = &stat->buf[i];

		/*
		 * Don't select the buffer which is being copied to
		 * userspace or used by the module.
		 */
		if (curr == stat->locked_buf || curr == stat->active_buf)
			continue;

		/* Don't select uninitialised buffers if it's not required */
		if (!look_empty && curr->empty)
			continue;

		/* Pick uninitialised buffer over anything else if look_empty */
		if (curr->empty) {
			found = curr;
			break;
		}

		/* Choose the oldest buffer */
		if (!found ||
		    (s32)curr->frame_number - (s32)found->frame_number < 0)
			found = curr;
	}

	return found;
}