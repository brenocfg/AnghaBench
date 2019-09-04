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
struct workqueue_struct {int dummy; } ;
struct continuation {int /*<<< orphan*/  ws; } ;

/* Variables and functions */
 int /*<<< orphan*/  queue_work (struct workqueue_struct*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void queue_continuation(struct workqueue_struct *wq,
				      struct continuation *k)
{
	queue_work(wq, &k->ws);
}