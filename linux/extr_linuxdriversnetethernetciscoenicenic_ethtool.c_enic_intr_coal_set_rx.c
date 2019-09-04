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
typedef  int /*<<< orphan*/  u32 ;
struct enic {int rq_count; int /*<<< orphan*/ * intr; } ;

/* Variables and functions */
 int enic_msix_rq_intr (struct enic*,int) ; 
 int /*<<< orphan*/  vnic_intr_coalescing_timer_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void enic_intr_coal_set_rx(struct enic *enic, u32 timer)
{
	int i;
	int intr;

	for (i = 0; i < enic->rq_count; i++) {
		intr = enic_msix_rq_intr(enic, i);
		vnic_intr_coalescing_timer_set(&enic->intr[intr], timer);
	}
}