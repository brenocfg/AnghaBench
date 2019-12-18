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
struct scsi_device {TYPE_1__* host; } ;
struct block_device {int dummy; } ;
typedef  int sector_t ;
struct TYPE_2__ {scalar_t__ hostdata; } ;
typedef  int /*<<< orphan*/  TW_Device_Extension ;

/* Variables and functions */
 int sector_div (int,int) ; 

__attribute__((used)) static int twl_scsi_biosparam(struct scsi_device *sdev, struct block_device *bdev, sector_t capacity, int geom[])
{
	int heads, sectors;
	TW_Device_Extension *tw_dev;

	tw_dev = (TW_Device_Extension *)sdev->host->hostdata;

	if (capacity >= 0x200000) {
		heads = 255;
		sectors = 63;
	} else {
		heads = 64;
		sectors = 32;
	}

	geom[0] = heads;
	geom[1] = sectors;
	geom[2] = sector_div(capacity, heads * sectors); /* cylinders */

	return 0;
}