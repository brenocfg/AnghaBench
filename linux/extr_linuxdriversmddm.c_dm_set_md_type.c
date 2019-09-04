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
struct mapped_device {int type; int /*<<< orphan*/  type_lock; } ;
typedef  enum dm_queue_mode { ____Placeholder_dm_queue_mode } dm_queue_mode ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  mutex_is_locked (int /*<<< orphan*/ *) ; 

void dm_set_md_type(struct mapped_device *md, enum dm_queue_mode type)
{
	BUG_ON(!mutex_is_locked(&md->type_lock));
	md->type = type;
}