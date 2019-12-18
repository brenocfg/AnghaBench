#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ curr_nr; scalar_t__ min_nr; } ;
typedef  TYPE_1__ mempool_t ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  mempool_alloc (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mempool_free (int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static void mempool_refill(mempool_t *pool)
{
	while (pool->curr_nr < pool->min_nr)
		mempool_free(mempool_alloc(pool, GFP_KERNEL), pool);
}