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
struct scsi_device {int /*<<< orphan*/  host; } ;
struct myrb_hba {int ldev_geom_heads; int ldev_geom_sectors; } ;
struct block_device {int dummy; } ;
typedef  int /*<<< orphan*/  sector_t ;

/* Variables and functions */
 int sector_div (int /*<<< orphan*/ ,int) ; 
 struct myrb_hba* shost_priv (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int myrb_biosparam(struct scsi_device *sdev, struct block_device *bdev,
		sector_t capacity, int geom[])
{
	struct myrb_hba *cb = shost_priv(sdev->host);

	geom[0] = cb->ldev_geom_heads;
	geom[1] = cb->ldev_geom_sectors;
	geom[2] = sector_div(capacity, geom[0] * geom[1]);

	return 0;
}