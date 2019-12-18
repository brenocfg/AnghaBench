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
struct cdrom_info {int /*<<< orphan*/  drive; } ;

/* Variables and functions */
 int /*<<< orphan*/  cdrom_info ; 
 int /*<<< orphan*/  ide_cd_read_toc (int /*<<< orphan*/ ) ; 
 struct cdrom_info* ide_drv_g (struct gendisk*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int idecd_revalidate_disk(struct gendisk *disk)
{
	struct cdrom_info *info = ide_drv_g(disk, cdrom_info);

	ide_cd_read_toc(info->drive);

	return  0;
}