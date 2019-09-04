#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct block_device {TYPE_1__* bd_disk; } ;
struct bcache_device {int /*<<< orphan*/  cl; int /*<<< orphan*/  flags; } ;
typedef  int /*<<< orphan*/  fmode_t ;
struct TYPE_2__ {struct bcache_device* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  BCACHE_DEV_CLOSING ; 
 int ENXIO ; 
 int /*<<< orphan*/  closure_get (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int open_dev(struct block_device *b, fmode_t mode)
{
	struct bcache_device *d = b->bd_disk->private_data;

	if (test_bit(BCACHE_DEV_CLOSING, &d->flags))
		return -ENXIO;

	closure_get(&d->cl);
	return 0;
}