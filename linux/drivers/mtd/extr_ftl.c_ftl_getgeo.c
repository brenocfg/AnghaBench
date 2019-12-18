#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u_long ;
struct mtd_blktrans_dev {int dummy; } ;
struct hd_geometry {int heads; int sectors; int cylinders; } ;
struct TYPE_3__ {int /*<<< orphan*/  FormattedSize; } ;
struct TYPE_4__ {TYPE_1__ header; } ;
typedef  TYPE_2__ partition_t ;

/* Variables and functions */
 int SECTOR_SIZE ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ftl_getgeo(struct mtd_blktrans_dev *dev, struct hd_geometry *geo)
{
	partition_t *part = (void *)dev;
	u_long sect;

	/* Sort of arbitrary: round size down to 4KiB boundary */
	sect = le32_to_cpu(part->header.FormattedSize)/SECTOR_SIZE;

	geo->heads = 1;
	geo->sectors = 8;
	geo->cylinders = sect >> 3;

	return 0;
}