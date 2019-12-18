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
struct prefetch_set {scalar_t__* blocks; int /*<<< orphan*/  lock; } ;
typedef  scalar_t__ dm_block_t ;

/* Variables and functions */
 scalar_t__ PREFETCH_SENTINEL ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 unsigned int prefetch_hash (scalar_t__) ; 

__attribute__((used)) static void prefetch_add(struct prefetch_set *p, dm_block_t b)
{
	unsigned h = prefetch_hash(b);

	mutex_lock(&p->lock);
	if (p->blocks[h] == PREFETCH_SENTINEL)
		p->blocks[h] = b;

	mutex_unlock(&p->lock);
}