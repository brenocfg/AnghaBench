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
struct request_queue {int dummy; } ;
struct hd_struct {unsigned long stamp; } ;

/* Variables and functions */
 int /*<<< orphan*/  __part_stat_add (int,struct hd_struct*,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  io_ticks ; 
 int /*<<< orphan*/  time_in_queue ; 

__attribute__((used)) static void part_round_stats_single(struct request_queue *q, int cpu,
				    struct hd_struct *part, unsigned long now,
				    unsigned int inflight)
{
	if (inflight) {
		__part_stat_add(cpu, part, time_in_queue,
				inflight * (now - part->stamp));
		__part_stat_add(cpu, part, io_ticks, (now - part->stamp));
	}
	part->stamp = now;
}