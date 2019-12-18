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
struct scsi_cd {int /*<<< orphan*/  cdi; TYPE_1__* device; } ;
struct gendisk {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  disk_events_disable_depth; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 unsigned int cdrom_check_events (int /*<<< orphan*/ *,unsigned int) ; 
 struct scsi_cd* scsi_cd_get (struct gendisk*) ; 
 int /*<<< orphan*/  scsi_cd_put (struct scsi_cd*) ; 

__attribute__((used)) static unsigned int sr_block_check_events(struct gendisk *disk,
					  unsigned int clearing)
{
	unsigned int ret = 0;
	struct scsi_cd *cd;

	cd = scsi_cd_get(disk);
	if (!cd)
		return 0;

	if (!atomic_read(&cd->device->disk_events_disable_depth))
		ret = cdrom_check_events(&cd->cdi, clearing);

	scsi_cd_put(cd);
	return ret;
}