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
struct etnaviv_gem_object {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

void etnaviv_gem_put_pages(struct etnaviv_gem_object *etnaviv_obj)
{
	lockdep_assert_held(&etnaviv_obj->lock);
	/* when we start tracking the pin count, then do something here */
}