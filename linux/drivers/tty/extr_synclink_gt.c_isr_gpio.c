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
struct slgt_info {struct cond_wait* gpio_wait_q; } ;
struct cond_wait {unsigned int data; struct cond_wait* next; int /*<<< orphan*/  q; } ;

/* Variables and functions */
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void isr_gpio(struct slgt_info *info, unsigned int changed, unsigned int state)
{
	struct cond_wait *w, *prev;

	/* wake processes waiting for specific transitions */
	for (w = info->gpio_wait_q, prev = NULL ; w != NULL ; w = w->next) {
		if (w->data & changed) {
			w->data = state;
			wake_up_interruptible(&w->q);
			if (prev != NULL)
				prev->next = w->next;
			else
				info->gpio_wait_q = w->next;
		} else
			prev = w;
	}
}