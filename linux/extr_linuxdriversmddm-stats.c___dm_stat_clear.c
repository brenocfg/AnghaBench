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
struct TYPE_2__ {scalar_t__* histogram; scalar_t__ time_in_queue; scalar_t__ io_ticks_total; scalar_t__* io_ticks; scalar_t__* ticks; scalar_t__* merges; scalar_t__* ios; scalar_t__* sectors; } ;
struct dm_stat_shared {TYPE_1__ tmp; } ;
struct dm_stat_percpu {int /*<<< orphan*/ * histogram; int /*<<< orphan*/  time_in_queue; int /*<<< orphan*/  io_ticks_total; int /*<<< orphan*/ * io_ticks; int /*<<< orphan*/ * ticks; int /*<<< orphan*/ * merges; int /*<<< orphan*/ * ios; int /*<<< orphan*/ * sectors; } ;
struct dm_stat {int n_histogram_entries; struct dm_stat_percpu** stat_percpu; struct dm_stat_shared* stat_shared; } ;

/* Variables and functions */
 size_t READ ; 
 size_t WRITE ; 
 int /*<<< orphan*/  __dm_stat_init_temporary_percpu_totals (struct dm_stat_shared*,struct dm_stat*,size_t) ; 
 int /*<<< orphan*/  local_irq_disable () ; 
 int /*<<< orphan*/  local_irq_enable () ; 
 size_t smp_processor_id () ; 

__attribute__((used)) static void __dm_stat_clear(struct dm_stat *s, size_t idx_start, size_t idx_end,
			    bool init_tmp_percpu_totals)
{
	size_t x;
	struct dm_stat_shared *shared;
	struct dm_stat_percpu *p;

	for (x = idx_start; x < idx_end; x++) {
		shared = &s->stat_shared[x];
		if (init_tmp_percpu_totals)
			__dm_stat_init_temporary_percpu_totals(shared, s, x);
		local_irq_disable();
		p = &s->stat_percpu[smp_processor_id()][x];
		p->sectors[READ] -= shared->tmp.sectors[READ];
		p->sectors[WRITE] -= shared->tmp.sectors[WRITE];
		p->ios[READ] -= shared->tmp.ios[READ];
		p->ios[WRITE] -= shared->tmp.ios[WRITE];
		p->merges[READ] -= shared->tmp.merges[READ];
		p->merges[WRITE] -= shared->tmp.merges[WRITE];
		p->ticks[READ] -= shared->tmp.ticks[READ];
		p->ticks[WRITE] -= shared->tmp.ticks[WRITE];
		p->io_ticks[READ] -= shared->tmp.io_ticks[READ];
		p->io_ticks[WRITE] -= shared->tmp.io_ticks[WRITE];
		p->io_ticks_total -= shared->tmp.io_ticks_total;
		p->time_in_queue -= shared->tmp.time_in_queue;
		local_irq_enable();
		if (s->n_histogram_entries) {
			unsigned i;
			for (i = 0; i < s->n_histogram_entries + 1; i++) {
				local_irq_disable();
				p = &s->stat_percpu[smp_processor_id()][x];
				p->histogram[i] -= shared->tmp.histogram[i];
				local_irq_enable();
			}
		}
	}
}