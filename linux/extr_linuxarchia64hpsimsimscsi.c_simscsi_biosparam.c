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

__attribute__((used)) static int
simscsi_biosparam (struct scsi_device *sdev, struct block_device *n,
		sector_t capacity, int ip[])
{
	ip[0] = 64;		/* heads */
	ip[1] = 32;		/* sectors */
	ip[2] = capacity >> 11;	/* cylinders */
	return 0;
}