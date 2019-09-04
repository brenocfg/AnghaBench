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
struct gendisk {int dummy; } ;
struct cdrom_info {int /*<<< orphan*/  devinfo; } ;

/* Variables and functions */
 unsigned int cdrom_check_events (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  cdrom_info ; 
 struct cdrom_info* ide_drv_g (struct gendisk*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int idecd_check_events(struct gendisk *disk,
				       unsigned int clearing)
{
	struct cdrom_info *info = ide_drv_g(disk, cdrom_info);
	return cdrom_check_events(&info->devinfo, clearing);
}