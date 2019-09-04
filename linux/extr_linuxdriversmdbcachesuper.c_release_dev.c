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
struct gendisk {struct bcache_device* private_data; } ;
struct bcache_device {int /*<<< orphan*/  cl; } ;
typedef  int /*<<< orphan*/  fmode_t ;

/* Variables and functions */
 int /*<<< orphan*/  closure_put (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void release_dev(struct gendisk *b, fmode_t mode)
{
	struct bcache_device *d = b->private_data;

	closure_put(&d->cl);
}