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
struct unstripe_c {int dummy; } ;
struct dm_target {struct unstripe_c* private; } ;

/* Variables and functions */
 int /*<<< orphan*/  cleanup_unstripe (struct unstripe_c*,struct dm_target*) ; 

__attribute__((used)) static void unstripe_dtr(struct dm_target *ti)
{
	struct unstripe_c *uc = ti->private;

	cleanup_unstripe(uc, ti);
}