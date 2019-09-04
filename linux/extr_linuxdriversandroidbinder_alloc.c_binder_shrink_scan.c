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
struct shrinker {int dummy; } ;
struct shrink_control {int /*<<< orphan*/  nr_to_scan; } ;

/* Variables and functions */
 int /*<<< orphan*/  binder_alloc_free_page ; 
 int /*<<< orphan*/  binder_alloc_lru ; 
 unsigned long list_lru_walk (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned long
binder_shrink_scan(struct shrinker *shrink, struct shrink_control *sc)
{
	unsigned long ret;

	ret = list_lru_walk(&binder_alloc_lru, binder_alloc_free_page,
			    NULL, sc->nr_to_scan);
	return ret;
}