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
struct background_tracker {int /*<<< orphan*/  work_cache; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct background_tracker*) ; 
 int /*<<< orphan*/  kmem_cache_destroy (int /*<<< orphan*/ ) ; 

void btracker_destroy(struct background_tracker *b)
{
	kmem_cache_destroy(b->work_cache);
	kfree(b);
}