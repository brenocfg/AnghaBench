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
typedef  int u32 ;
struct TYPE_2__ {unsigned long pages_mask; int /*<<< orphan*/  total_count; int /*<<< orphan*/ * entries; } ;

/* Variables and functions */
 int BITS_PER_LONG ; 
 unsigned long PAGE_SHIFT ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_and_set_bit (int,int /*<<< orphan*/ *) ; 
 TYPE_1__ wss ; 
 int /*<<< orphan*/  wss_advance_clean_counter () ; 

__attribute__((used)) static void wss_insert(void *address)
{
	u32 page = ((unsigned long)address >> PAGE_SHIFT) & wss.pages_mask;
	u32 entry = page / BITS_PER_LONG; /* assumes this ends up a shift */
	u32 nr = page & (BITS_PER_LONG - 1);

	if (!test_and_set_bit(nr, &wss.entries[entry]))
		atomic_inc(&wss.total_count);

	wss_advance_clean_counter();
}