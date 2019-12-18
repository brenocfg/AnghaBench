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
struct scsi_device {int dummy; } ;
struct block_device {int dummy; } ;
typedef  int sector_t ;

/* Variables and functions */
 int sector_div (int,int) ; 

__attribute__((used)) static int wd719x_biosparam(struct scsi_device *sdev, struct block_device *bdev,
			    sector_t capacity, int geom[])
{
	if (capacity >= 0x200000) {
		geom[0] = 255;	/* heads */
		geom[1] = 63;	/* sectors */
	} else {
		geom[0] = 64;	/* heads */
		geom[1] = 32;	/* sectors */
	}
	geom[2] = sector_div(capacity, geom[0] * geom[1]);	/* cylinders */

	return 0;
}