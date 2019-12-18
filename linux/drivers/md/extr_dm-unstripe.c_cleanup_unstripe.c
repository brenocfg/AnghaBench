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
struct unstripe_c {scalar_t__ dev; } ;
struct dm_target {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dm_put_device (struct dm_target*,scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct unstripe_c*) ; 

__attribute__((used)) static void cleanup_unstripe(struct unstripe_c *uc, struct dm_target *ti)
{
	if (uc->dev)
		dm_put_device(ti, uc->dev);
	kfree(uc);
}