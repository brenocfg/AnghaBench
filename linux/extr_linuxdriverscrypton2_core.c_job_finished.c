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
struct spu_queue {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline bool job_finished(struct spu_queue *q, unsigned int offset,
				unsigned long old_head, unsigned long new_head)
{
	if (old_head <= new_head) {
		if (offset > old_head && offset <= new_head)
			return true;
	} else {
		if (offset > old_head || offset <= new_head)
			return true;
	}
	return false;
}