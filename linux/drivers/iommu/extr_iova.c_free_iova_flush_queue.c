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
struct iova_domain {int /*<<< orphan*/ * entry_dtor; int /*<<< orphan*/ * flush_cb; int /*<<< orphan*/ * fq; int /*<<< orphan*/  fq_timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fq_destroy_all_entries (struct iova_domain*) ; 
 int /*<<< orphan*/  free_percpu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  has_iova_flush_queue (struct iova_domain*) ; 
 scalar_t__ timer_pending (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void free_iova_flush_queue(struct iova_domain *iovad)
{
	if (!has_iova_flush_queue(iovad))
		return;

	if (timer_pending(&iovad->fq_timer))
		del_timer(&iovad->fq_timer);

	fq_destroy_all_entries(iovad);

	free_percpu(iovad->fq);

	iovad->fq         = NULL;
	iovad->flush_cb   = NULL;
	iovad->entry_dtor = NULL;
}