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
struct nullb_device {int /*<<< orphan*/  badblocks; } ;

/* Variables and functions */
 int /*<<< orphan*/  badblocks_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct nullb_device*) ; 
 int /*<<< orphan*/  null_zone_exit (struct nullb_device*) ; 

__attribute__((used)) static void null_free_dev(struct nullb_device *dev)
{
	if (!dev)
		return;

	null_zone_exit(dev);
	badblocks_exit(&dev->badblocks);
	kfree(dev);
}