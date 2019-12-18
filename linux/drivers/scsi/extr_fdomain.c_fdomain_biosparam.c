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
 int /*<<< orphan*/  kfree (unsigned char*) ; 
 unsigned char* scsi_bios_ptable (struct block_device*) ; 
 int sector_div (int,int) ; 

__attribute__((used)) static int fdomain_biosparam(struct scsi_device *sdev,
			     struct block_device *bdev,	sector_t capacity,
			     int geom[])
{
	unsigned char *p = scsi_bios_ptable(bdev);

	if (p && p[65] == 0xaa && p[64] == 0x55 /* Partition table valid */
	    && p[4]) {	 /* Partition type */
		geom[0] = p[5] + 1;	/* heads */
		geom[1] = p[6] & 0x3f;	/* sectors */
	} else {
		if (capacity >= 0x7e0000) {
			geom[0] = 255;	/* heads */
			geom[1] = 63;	/* sectors */
		} else if (capacity >= 0x200000) {
			geom[0] = 128;	/* heads */
			geom[1] = 63;	/* sectors */
		} else {
			geom[0] = 64;	/* heads */
			geom[1] = 32;	/* sectors */
		}
	}
	geom[2] = sector_div(capacity, geom[0] * geom[1]);
	kfree(p);

	return 0;
}