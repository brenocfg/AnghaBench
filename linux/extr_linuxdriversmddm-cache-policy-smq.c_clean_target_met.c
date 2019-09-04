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
struct smq_policy {int /*<<< orphan*/  dirty; } ;

/* Variables and functions */
 unsigned int q_size (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool clean_target_met(struct smq_policy *mq, bool idle)
{
	/*
	 * Cache entries may not be populated.  So we cannot rely on the
	 * size of the clean queue.
	 */
	if (idle) {
		/*
		 * We'd like to clean everything.
		 */
		return q_size(&mq->dirty) == 0u;
	}

	/*
	 * If we're busy we don't worry about cleaning at all.
	 */
	return true;
}