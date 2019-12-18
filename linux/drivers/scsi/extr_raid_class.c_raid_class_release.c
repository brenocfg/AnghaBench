#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct raid_template {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  ac; } ;
struct TYPE_4__ {TYPE_1__ raid_attrs; } ;
struct raid_internal {TYPE_2__ r; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  attribute_container_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct raid_internal*) ; 
 struct raid_internal* to_raid_internal (struct raid_template*) ; 

void
raid_class_release(struct raid_template *r)
{
	struct raid_internal *i = to_raid_internal(r);

	BUG_ON(attribute_container_unregister(&i->r.raid_attrs.ac));

	kfree(i);
}