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
struct TYPE_2__ {int bucket_size; } ;
struct cache_set {int nbuckets; TYPE_1__ sb; int /*<<< orphan*/  sectors_to_gc; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static inline void set_gc_sectors(struct cache_set *c)
{
	atomic_set(&c->sectors_to_gc, c->sb.bucket_size * c->nbuckets / 16);
}