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
struct rxe_dev {int /*<<< orphan*/ * stats_counters; } ;
typedef  enum rxe_counters { ____Placeholder_rxe_counters } rxe_counters ;

/* Variables and functions */

__attribute__((used)) static inline void rxe_counter_inc(struct rxe_dev *rxe, enum rxe_counters cnt)
{
	rxe->stats_counters[cnt]++;
}