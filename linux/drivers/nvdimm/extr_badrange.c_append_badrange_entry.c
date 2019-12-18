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
typedef  void* u64 ;
struct badrange_entry {int /*<<< orphan*/  list; void* length; void* start; } ;
struct badrange {int /*<<< orphan*/  list; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void append_badrange_entry(struct badrange *badrange,
		struct badrange_entry *bre, u64 addr, u64 length)
{
	lockdep_assert_held(&badrange->lock);
	bre->start = addr;
	bre->length = length;
	list_add_tail(&bre->list, &badrange->list);
}