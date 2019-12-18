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
struct multipath {int /*<<< orphan*/  ti; } ;

/* Variables and functions */
 int /*<<< orphan*/  MPATHF_QUEUE_IF_NO_PATH ; 
 int /*<<< orphan*/  MPATHF_SAVED_QUEUE_IF_NO_PATH ; 
 scalar_t__ dm_noflush_suspending (int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,unsigned long*) ; 

__attribute__((used)) static bool __must_push_back(struct multipath *m, unsigned long flags)
{
	return ((test_bit(MPATHF_QUEUE_IF_NO_PATH, &flags) !=
		 test_bit(MPATHF_SAVED_QUEUE_IF_NO_PATH, &flags)) &&
		dm_noflush_suspending(m->ti));
}