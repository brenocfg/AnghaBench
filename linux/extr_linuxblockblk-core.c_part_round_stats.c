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
struct request_queue {int dummy; } ;
struct hd_struct {unsigned long stamp; scalar_t__ partno; } ;
struct TYPE_2__ {struct hd_struct part0; } ;

/* Variables and functions */
 unsigned long jiffies ; 
 int /*<<< orphan*/  part_in_flight (struct request_queue*,struct hd_struct*,unsigned int*) ; 
 int /*<<< orphan*/  part_round_stats_single (struct request_queue*,int,struct hd_struct*,unsigned long,unsigned int) ; 
 TYPE_1__* part_to_disk (struct hd_struct*) ; 

void part_round_stats(struct request_queue *q, int cpu, struct hd_struct *part)
{
	struct hd_struct *part2 = NULL;
	unsigned long now = jiffies;
	unsigned int inflight[2];
	int stats = 0;

	if (part->stamp != now)
		stats |= 1;

	if (part->partno) {
		part2 = &part_to_disk(part)->part0;
		if (part2->stamp != now)
			stats |= 2;
	}

	if (!stats)
		return;

	part_in_flight(q, part, inflight);

	if (stats & 2)
		part_round_stats_single(q, cpu, part2, now, inflight[1]);
	if (stats & 1)
		part_round_stats_single(q, cpu, part, now, inflight[0]);
}