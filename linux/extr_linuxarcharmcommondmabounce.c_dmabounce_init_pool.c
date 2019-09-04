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
struct dmabounce_pool {unsigned long size; scalar_t__ pool; scalar_t__ allocs; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DO_STATS (scalar_t__) ; 
 int ENOMEM ; 
 scalar_t__ dma_pool_create (char const*,struct device*,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dmabounce_init_pool(struct dmabounce_pool *pool, struct device *dev,
		const char *name, unsigned long size)
{
	pool->size = size;
	DO_STATS(pool->allocs = 0);
	pool->pool = dma_pool_create(name, dev, size,
				     0 /* byte alignment */,
				     0 /* no page-crossing issues */);

	return pool->pool ? 0 : -ENOMEM;
}