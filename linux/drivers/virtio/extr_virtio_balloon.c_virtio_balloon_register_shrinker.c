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
struct TYPE_2__ {int /*<<< orphan*/  seeks; int /*<<< orphan*/  count_objects; int /*<<< orphan*/  scan_objects; } ;
struct virtio_balloon {TYPE_1__ shrinker; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_SEEKS ; 
 int register_shrinker (TYPE_1__*) ; 
 int /*<<< orphan*/  virtio_balloon_shrinker_count ; 
 int /*<<< orphan*/  virtio_balloon_shrinker_scan ; 

__attribute__((used)) static int virtio_balloon_register_shrinker(struct virtio_balloon *vb)
{
	vb->shrinker.scan_objects = virtio_balloon_shrinker_scan;
	vb->shrinker.count_objects = virtio_balloon_shrinker_count;
	vb->shrinker.seeks = DEFAULT_SEEKS;

	return register_shrinker(&vb->shrinker);
}