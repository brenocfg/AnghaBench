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
struct dust_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  badblock_count; int /*<<< orphan*/  badblocklist; } ;
struct dm_target {struct dust_device* private; } ;

/* Variables and functions */
 int /*<<< orphan*/  __dust_clear_badblocks (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dm_put_device (struct dm_target*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct dust_device*) ; 

__attribute__((used)) static void dust_dtr(struct dm_target *ti)
{
	struct dust_device *dd = ti->private;

	__dust_clear_badblocks(&dd->badblocklist, dd->badblock_count);
	dm_put_device(ti, dd->dev);
	kfree(dd);
}