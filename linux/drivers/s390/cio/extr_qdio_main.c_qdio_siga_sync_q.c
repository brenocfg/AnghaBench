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
struct qdio_q {int /*<<< orphan*/  mask; scalar_t__ is_input_q; } ;

/* Variables and functions */
 int qdio_siga_sync (struct qdio_q*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int qdio_siga_sync_q(struct qdio_q *q)
{
	if (q->is_input_q)
		return qdio_siga_sync(q, 0, q->mask);
	else
		return qdio_siga_sync(q, q->mask, 0);
}