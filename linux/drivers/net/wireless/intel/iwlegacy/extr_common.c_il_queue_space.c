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
struct il_queue {int read_ptr; int write_ptr; scalar_t__ n_win; scalar_t__ n_bd; } ;

/* Variables and functions */

int
il_queue_space(const struct il_queue *q)
{
	int s = q->read_ptr - q->write_ptr;

	if (q->read_ptr > q->write_ptr)
		s -= q->n_bd;

	if (s <= 0)
		s += q->n_win;
	/* keep some reserve to not confuse empty and full situations */
	s -= 2;
	if (s < 0)
		s = 0;
	return s;
}