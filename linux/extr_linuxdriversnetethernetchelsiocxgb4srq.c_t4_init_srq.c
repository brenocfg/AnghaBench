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
struct srq_data {int srq_size; int /*<<< orphan*/  lock; int /*<<< orphan*/  comp; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 struct srq_data* kvzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

struct srq_data *t4_init_srq(int srq_size)
{
	struct srq_data *s;

	s = kvzalloc(sizeof(*s), GFP_KERNEL);
	if (!s)
		return NULL;

	s->srq_size = srq_size;
	init_completion(&s->comp);
	mutex_init(&s->lock);

	return s;
}