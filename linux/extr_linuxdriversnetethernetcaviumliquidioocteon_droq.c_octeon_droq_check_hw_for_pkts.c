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
typedef  scalar_t__ u32 ;
struct octeon_droq {int /*<<< orphan*/  pkts_pending; scalar_t__ pkt_count; int /*<<< orphan*/  pkts_sent_reg; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_add (scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ readl (int /*<<< orphan*/ ) ; 

u32 octeon_droq_check_hw_for_pkts(struct octeon_droq *droq)
{
	u32 pkt_count = 0;
	u32 last_count;

	pkt_count = readl(droq->pkts_sent_reg);

	last_count = pkt_count - droq->pkt_count;
	droq->pkt_count = pkt_count;

	/* we shall write to cnts  at napi irq enable or end of droq tasklet */
	if (last_count)
		atomic_add(last_count, &droq->pkts_pending);

	return last_count;
}