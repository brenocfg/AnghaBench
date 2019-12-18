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
struct ccw1 {scalar_t__ count; } ;

/* Variables and functions */
 scalar_t__ ccw_is_noop (struct ccw1*) ; 
 scalar_t__ ccw_is_read (struct ccw1*) ; 
 scalar_t__ ccw_is_read_backward (struct ccw1*) ; 
 scalar_t__ ccw_is_sense (struct ccw1*) ; 
 int /*<<< orphan*/  ccw_is_skip (struct ccw1*) ; 

__attribute__((used)) static inline int ccw_does_data_transfer(struct ccw1 *ccw)
{
	/* If the count field is zero, then no data will be transferred */
	if (ccw->count == 0)
		return 0;

	/* If the command is a NOP, then no data will be transferred */
	if (ccw_is_noop(ccw))
		return 0;

	/* If the skip flag is off, then data will be transferred */
	if (!ccw_is_skip(ccw))
		return 1;

	/*
	 * If the skip flag is on, it is only meaningful if the command
	 * code is a read, read backward, sense, or sense ID.  In those
	 * cases, no data will be transferred.
	 */
	if (ccw_is_read(ccw) || ccw_is_read_backward(ccw))
		return 0;

	if (ccw_is_sense(ccw))
		return 0;

	/* The skip flag is on, but it is ignored for this command code. */
	return 1;
}