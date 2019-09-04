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
typedef  scalar_t__ u16 ;
struct ide_disk_obj {TYPE_1__* drive; } ;
struct hd_geometry {scalar_t__ cylinders; int /*<<< orphan*/  sectors; int /*<<< orphan*/  heads; } ;
struct block_device {int /*<<< orphan*/  bd_disk; } ;
struct TYPE_2__ {scalar_t__ bios_cyl; int /*<<< orphan*/  bios_sect; int /*<<< orphan*/  bios_head; } ;
typedef  TYPE_1__ ide_drive_t ;

/* Variables and functions */
 int /*<<< orphan*/  ide_disk_obj ; 
 struct ide_disk_obj* ide_drv_g (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ide_gd_getgeo(struct block_device *bdev, struct hd_geometry *geo)
{
	struct ide_disk_obj *idkp = ide_drv_g(bdev->bd_disk, ide_disk_obj);
	ide_drive_t *drive = idkp->drive;

	geo->heads = drive->bios_head;
	geo->sectors = drive->bios_sect;
	geo->cylinders = (u16)drive->bios_cyl; /* truncate */
	return 0;
}