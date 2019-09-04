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
struct mddev {int /*<<< orphan*/  openers; } ;
struct gendisk {struct mddev* private_data; } ;
typedef  int /*<<< orphan*/  fmode_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mddev_put (struct mddev*) ; 

__attribute__((used)) static void md_release(struct gendisk *disk, fmode_t mode)
{
	struct mddev *mddev = disk->private_data;

	BUG_ON(!mddev);
	atomic_dec(&mddev->openers);
	mddev_put(mddev);
}