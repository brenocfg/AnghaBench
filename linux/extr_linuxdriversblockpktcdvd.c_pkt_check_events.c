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
struct pktcdvd_device {TYPE_1__* bdev; } ;
struct gendisk {TYPE_2__* fops; struct pktcdvd_device* private_data; } ;
struct TYPE_4__ {unsigned int (* check_events ) (struct gendisk*,unsigned int) ;} ;
struct TYPE_3__ {struct gendisk* bd_disk; } ;

/* Variables and functions */
 unsigned int stub1 (struct gendisk*,unsigned int) ; 

__attribute__((used)) static unsigned int pkt_check_events(struct gendisk *disk,
				     unsigned int clearing)
{
	struct pktcdvd_device *pd = disk->private_data;
	struct gendisk *attached_disk;

	if (!pd)
		return 0;
	if (!pd->bdev)
		return 0;
	attached_disk = pd->bdev->bd_disk;
	if (!attached_disk || !attached_disk->fops->check_events)
		return 0;
	return attached_disk->fops->check_events(attached_disk, clearing);
}