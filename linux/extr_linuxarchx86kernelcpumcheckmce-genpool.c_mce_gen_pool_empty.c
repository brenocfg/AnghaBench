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

/* Variables and functions */
 int llist_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mce_event_llist ; 

bool mce_gen_pool_empty(void)
{
	return llist_empty(&mce_event_llist);
}