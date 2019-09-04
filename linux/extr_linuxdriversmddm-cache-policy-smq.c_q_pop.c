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
struct queue {int /*<<< orphan*/  nr_levels; } ;
struct entry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  q_del (struct queue*,struct entry*) ; 
 struct entry* q_peek (struct queue*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static struct entry *q_pop(struct queue *q)
{
	struct entry *e = q_peek(q, q->nr_levels, true);

	if (e)
		q_del(q, e);

	return e;
}