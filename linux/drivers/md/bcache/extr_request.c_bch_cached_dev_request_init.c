#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct gendisk {TYPE_2__* queue; } ;
struct TYPE_6__ {int /*<<< orphan*/  ioctl; int /*<<< orphan*/  cache_miss; struct gendisk* disk; } ;
struct cached_dev {TYPE_3__ disk; } ;
struct TYPE_5__ {TYPE_1__* backing_dev_info; int /*<<< orphan*/  make_request_fn; } ;
struct TYPE_4__ {int /*<<< orphan*/  congested_fn; } ;

/* Variables and functions */
 int /*<<< orphan*/  cached_dev_cache_miss ; 
 int /*<<< orphan*/  cached_dev_congested ; 
 int /*<<< orphan*/  cached_dev_ioctl ; 
 int /*<<< orphan*/  cached_dev_make_request ; 

void bch_cached_dev_request_init(struct cached_dev *dc)
{
	struct gendisk *g = dc->disk.disk;

	g->queue->make_request_fn		= cached_dev_make_request;
	g->queue->backing_dev_info->congested_fn = cached_dev_congested;
	dc->disk.cache_miss			= cached_dev_cache_miss;
	dc->disk.ioctl				= cached_dev_ioctl;
}