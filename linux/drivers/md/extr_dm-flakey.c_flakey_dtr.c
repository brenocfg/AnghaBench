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
struct flakey_c {int /*<<< orphan*/  dev; } ;
struct dm_target {struct flakey_c* private; } ;

/* Variables and functions */
 int /*<<< orphan*/  dm_put_device (struct dm_target*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct flakey_c*) ; 

__attribute__((used)) static void flakey_dtr(struct dm_target *ti)
{
	struct flakey_c *fc = ti->private;

	dm_put_device(ti, fc->dev);
	kfree(fc);
}