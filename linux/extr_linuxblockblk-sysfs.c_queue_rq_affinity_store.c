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
struct request_queue {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 

__attribute__((used)) static ssize_t
queue_rq_affinity_store(struct request_queue *q, const char *page, size_t count)
{
	ssize_t ret = -EINVAL;
#ifdef CONFIG_SMP
	unsigned long val;

	ret = queue_var_store(&val, page, count);
	if (ret < 0)
		return ret;

	spin_lock_irq(q->queue_lock);
	if (val == 2) {
		queue_flag_set(QUEUE_FLAG_SAME_COMP, q);
		queue_flag_set(QUEUE_FLAG_SAME_FORCE, q);
	} else if (val == 1) {
		queue_flag_set(QUEUE_FLAG_SAME_COMP, q);
		queue_flag_clear(QUEUE_FLAG_SAME_FORCE, q);
	} else if (val == 0) {
		queue_flag_clear(QUEUE_FLAG_SAME_COMP, q);
		queue_flag_clear(QUEUE_FLAG_SAME_FORCE, q);
	}
	spin_unlock_irq(q->queue_lock);
#endif
	return ret;
}