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
typedef  int /*<<< orphan*/  fmode_t ;

/* Variables and functions */
 int /*<<< orphan*/  cdrom_info ; 
 int /*<<< orphan*/  cdrom_release (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ide_cd_mutex ; 
 int /*<<< orphan*/  ide_cd_put (struct cdrom_info*) ; 
 struct cdrom_info* ide_drv_g (struct gendisk*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void idecd_release(struct gendisk *disk, fmode_t mode)
{
	struct cdrom_info *info = ide_drv_g(disk, cdrom_info);

	mutex_lock(&ide_cd_mutex);
	cdrom_release(&info->devinfo, mode);

	ide_cd_put(info);
	mutex_unlock(&ide_cd_mutex);
}