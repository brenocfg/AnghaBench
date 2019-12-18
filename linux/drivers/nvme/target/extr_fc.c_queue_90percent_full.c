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
typedef  int u32 ;
struct nvmet_fc_tgt_queue {int sqsize; int /*<<< orphan*/  sqtail; } ;

/* Variables and functions */
 int atomic_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool
queue_90percent_full(struct nvmet_fc_tgt_queue *q, u32 sqhd)
{
	u32 sqtail, used;

	/* egad, this is ugly. And sqtail is just a best guess */
	sqtail = atomic_read(&q->sqtail) % q->sqsize;

	used = (sqtail < sqhd) ? (sqtail + q->sqsize - sqhd) : (sqtail - sqhd);
	return ((used * 10) >= (((u32)(q->sqsize - 1) * 9)));
}