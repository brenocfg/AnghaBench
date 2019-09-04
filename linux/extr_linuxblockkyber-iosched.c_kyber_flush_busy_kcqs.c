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
struct list_head {int dummy; } ;
struct kyber_hctx_data {int /*<<< orphan*/ * kcq_map; } ;
struct flush_kcq_data {unsigned int sched_domain; struct list_head* list; struct kyber_hctx_data* khd; } ;

/* Variables and functions */
 int /*<<< orphan*/  flush_busy_kcq ; 
 int /*<<< orphan*/  sbitmap_for_each_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct flush_kcq_data*) ; 

__attribute__((used)) static void kyber_flush_busy_kcqs(struct kyber_hctx_data *khd,
				  unsigned int sched_domain,
				  struct list_head *list)
{
	struct flush_kcq_data data = {
		.khd = khd,
		.sched_domain = sched_domain,
		.list = list,
	};

	sbitmap_for_each_set(&khd->kcq_map[sched_domain],
			     flush_busy_kcq, &data);
}