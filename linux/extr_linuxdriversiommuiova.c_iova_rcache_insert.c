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
struct iova_domain {int /*<<< orphan*/ * rcaches; } ;

/* Variables and functions */
 unsigned int IOVA_RANGE_CACHE_MAX_SIZE ; 
 int __iova_rcache_insert (struct iova_domain*,int /*<<< orphan*/ *,unsigned long) ; 
 unsigned int order_base_2 (unsigned long) ; 

__attribute__((used)) static bool iova_rcache_insert(struct iova_domain *iovad, unsigned long pfn,
			       unsigned long size)
{
	unsigned int log_size = order_base_2(size);

	if (log_size >= IOVA_RANGE_CACHE_MAX_SIZE)
		return false;

	return __iova_rcache_insert(iovad, &iovad->rcaches[log_size], pfn);
}