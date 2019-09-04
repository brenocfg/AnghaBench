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
struct cfq_queue {int dummy; } ;
struct cfq_io_cq {struct cfq_queue** cfqq; } ;

/* Variables and functions */

__attribute__((used)) static inline struct cfq_queue *cic_to_cfqq(struct cfq_io_cq *cic, bool is_sync)
{
	return cic->cfqq[is_sync];
}