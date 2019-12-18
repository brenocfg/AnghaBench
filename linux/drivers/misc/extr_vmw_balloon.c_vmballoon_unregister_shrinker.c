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
struct vmballoon {int shrinker_registered; int /*<<< orphan*/  shrinker; } ;

/* Variables and functions */
 int /*<<< orphan*/  unregister_shrinker (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void vmballoon_unregister_shrinker(struct vmballoon *b)
{
	if (b->shrinker_registered)
		unregister_shrinker(&b->shrinker);
	b->shrinker_registered = false;
}