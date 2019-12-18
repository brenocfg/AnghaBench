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
struct iova_rcache {int /*<<< orphan*/  cpu_rcaches; } ;
struct iova_domain {struct iova_rcache* rcaches; } ;
struct iova_cpu_rcache {int /*<<< orphan*/  lock; int /*<<< orphan*/  prev; int /*<<< orphan*/  loaded; } ;

/* Variables and functions */
 int IOVA_RANGE_CACHE_MAX_SIZE ; 
 int /*<<< orphan*/  iova_magazine_free_pfns (int /*<<< orphan*/ ,struct iova_domain*) ; 
 struct iova_cpu_rcache* per_cpu_ptr (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void free_cpu_cached_iovas(unsigned int cpu, struct iova_domain *iovad)
{
	struct iova_cpu_rcache *cpu_rcache;
	struct iova_rcache *rcache;
	unsigned long flags;
	int i;

	for (i = 0; i < IOVA_RANGE_CACHE_MAX_SIZE; ++i) {
		rcache = &iovad->rcaches[i];
		cpu_rcache = per_cpu_ptr(rcache->cpu_rcaches, cpu);
		spin_lock_irqsave(&cpu_rcache->lock, flags);
		iova_magazine_free_pfns(cpu_rcache->loaded, iovad);
		iova_magazine_free_pfns(cpu_rcache->prev, iovad);
		spin_unlock_irqrestore(&cpu_rcache->lock, flags);
	}
}