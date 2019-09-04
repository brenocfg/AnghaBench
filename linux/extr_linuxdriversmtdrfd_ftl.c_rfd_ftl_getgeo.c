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
struct partition {int /*<<< orphan*/  cylinders; } ;
struct mtd_blktrans_dev {int dummy; } ;
struct hd_geometry {int heads; int /*<<< orphan*/  cylinders; int /*<<< orphan*/  sectors; } ;

/* Variables and functions */
 int /*<<< orphan*/  SECTORS_PER_TRACK ; 

__attribute__((used)) static int rfd_ftl_getgeo(struct mtd_blktrans_dev *dev, struct hd_geometry *geo)
{
	struct partition *part = (struct partition*)dev;

	geo->heads = 1;
	geo->sectors = SECTORS_PER_TRACK;
	geo->cylinders = part->cylinders;

	return 0;
}