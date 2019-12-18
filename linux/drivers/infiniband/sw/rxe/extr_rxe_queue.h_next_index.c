#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct rxe_queue {TYPE_1__* buf; } ;
struct TYPE_2__ {int index_mask; } ;

/* Variables and functions */

__attribute__((used)) static inline int next_index(struct rxe_queue *q, int index)
{
	return (index + 1) & q->buf->index_mask;
}