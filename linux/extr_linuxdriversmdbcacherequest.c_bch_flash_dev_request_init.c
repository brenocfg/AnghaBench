#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct gendisk {TYPE_2__* queue; } ;
struct bcache_device {int /*<<< orphan*/  ioctl; int /*<<< orphan*/  cache_miss; struct gendisk* disk; } ;
struct TYPE_4__ {TYPE_1__* backing_dev_info; int /*<<< orphan*/  make_request_fn; } ;
struct TYPE_3__ {int /*<<< orphan*/  congested_fn; } ;

/* Variables and functions */
 int /*<<< orphan*/  flash_dev_cache_miss ; 
 int /*<<< orphan*/  flash_dev_congested ; 
 int /*<<< orphan*/  flash_dev_ioctl ; 
 int /*<<< orphan*/  flash_dev_make_request ; 

void bch_flash_dev_request_init(struct bcache_device *d)
{
	struct gendisk *g = d->disk;

	g->queue->make_request_fn		= flash_dev_make_request;
	g->queue->backing_dev_info->congested_fn = flash_dev_congested;
	d->cache_miss				= flash_dev_cache_miss;
	d->ioctl				= flash_dev_ioctl;
}