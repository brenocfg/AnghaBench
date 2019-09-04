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
struct pd_unit {int changed; int /*<<< orphan*/  removable; } ;
struct gendisk {struct pd_unit* private_data; } ;

/* Variables and functions */
 unsigned int DISK_EVENT_MEDIA_CHANGE ; 
 int /*<<< orphan*/  pd_media_check ; 
 int /*<<< orphan*/  pd_special_command (struct pd_unit*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int pd_check_events(struct gendisk *p, unsigned int clearing)
{
	struct pd_unit *disk = p->private_data;
	int r;
	if (!disk->removable)
		return 0;
	pd_special_command(disk, pd_media_check);
	r = disk->changed;
	disk->changed = 0;
	return r ? DISK_EVENT_MEDIA_CHANGE : 0;
}