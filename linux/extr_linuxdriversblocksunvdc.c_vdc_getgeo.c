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
struct hd_geometry {int heads; int sectors; int cylinders; } ;
struct gendisk {int dummy; } ;
struct block_device {struct gendisk* bd_disk; } ;
typedef  int sector_t ;

/* Variables and functions */
 int get_capacity (struct gendisk*) ; 
 int /*<<< orphan*/  sector_div (int,int) ; 

__attribute__((used)) static int vdc_getgeo(struct block_device *bdev, struct hd_geometry *geo)
{
	struct gendisk *disk = bdev->bd_disk;
	sector_t nsect = get_capacity(disk);
	sector_t cylinders = nsect;

	geo->heads = 0xff;
	geo->sectors = 0x3f;
	sector_div(cylinders, geo->heads * geo->sectors);
	geo->cylinders = cylinders;
	if ((sector_t)(geo->cylinders + 1) * geo->heads * geo->sectors < nsect)
		geo->cylinders = 0xffff;

	return 0;
}