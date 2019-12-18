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
struct TYPE_2__ {int /*<<< orphan*/  seeks; int /*<<< orphan*/  count_objects; int /*<<< orphan*/  scan_objects; } ;
struct vmballoon {int shrinker_registered; TYPE_1__ shrinker; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_SEEKS ; 
 int register_shrinker (TYPE_1__*) ; 
 int /*<<< orphan*/  vmballoon_shrinker_count ; 
 int /*<<< orphan*/  vmballoon_shrinker_scan ; 
 int /*<<< orphan*/  vmwballoon_shrinker_enable ; 

__attribute__((used)) static int vmballoon_register_shrinker(struct vmballoon *b)
{
	int r;

	/* Do nothing if the shrinker is not enabled */
	if (!vmwballoon_shrinker_enable)
		return 0;

	b->shrinker.scan_objects = vmballoon_shrinker_scan;
	b->shrinker.count_objects = vmballoon_shrinker_count;
	b->shrinker.seeks = DEFAULT_SEEKS;

	r = register_shrinker(&b->shrinker);

	if (r == 0)
		b->shrinker_registered = true;

	return r;
}