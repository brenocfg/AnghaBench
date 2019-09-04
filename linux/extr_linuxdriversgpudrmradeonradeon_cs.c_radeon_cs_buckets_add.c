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
struct radeon_cs_buckets {int /*<<< orphan*/ * bucket; } ;
struct list_head {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RADEON_CS_MAX_PRIORITY ; 
 int /*<<< orphan*/  list_add_tail (struct list_head*,int /*<<< orphan*/ *) ; 
 size_t min (unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void radeon_cs_buckets_add(struct radeon_cs_buckets *b,
				  struct list_head *item, unsigned priority)
{
	/* Since buffers which appear sooner in the relocation list are
	 * likely to be used more often than buffers which appear later
	 * in the list, the sort mustn't change the ordering of buffers
	 * with the same priority, i.e. it must be stable.
	 */
	list_add_tail(item, &b->bucket[min(priority, RADEON_CS_MAX_PRIORITY)]);
}