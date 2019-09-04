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
struct t4_srq {int /*<<< orphan*/  ooo_count; int /*<<< orphan*/  in_use; } ;

/* Variables and functions */

__attribute__((used)) static inline void t4_srq_produce_ooo(struct t4_srq *srq)
{
	srq->in_use--;
	srq->ooo_count++;
}