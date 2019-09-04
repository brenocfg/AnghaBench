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
struct dm_target {struct dm_origin* private; } ;
struct dm_origin {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __remove_dm_origin (struct dm_origin*) ; 
 int /*<<< orphan*/  _origins_lock ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void origin_postsuspend(struct dm_target *ti)
{
	struct dm_origin *o = ti->private;

	down_write(&_origins_lock);
	__remove_dm_origin(o);
	up_write(&_origins_lock);
}