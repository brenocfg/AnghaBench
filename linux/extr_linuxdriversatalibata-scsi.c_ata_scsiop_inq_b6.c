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
typedef  int u8 ;
struct ata_scsi_args {TYPE_1__* dev; } ;
struct TYPE_2__ {int zac_zoned_cap; int /*<<< orphan*/  zac_zones_max_open; int /*<<< orphan*/  zac_zones_optimal_nonseq; int /*<<< orphan*/  zac_zones_optimal_open; } ;

/* Variables and functions */
 int /*<<< orphan*/  put_unaligned_be32 (int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static unsigned int ata_scsiop_inq_b6(struct ata_scsi_args *args, u8 *rbuf)
{
	/*
	 * zbc-r05 SCSI Zoned Block device characteristics VPD page
	 */
	rbuf[1] = 0xb6;
	rbuf[3] = 0x3C;

	/*
	 * URSWRZ bit is only meaningful for host-managed ZAC drives
	 */
	if (args->dev->zac_zoned_cap & 1)
		rbuf[4] |= 1;
	put_unaligned_be32(args->dev->zac_zones_optimal_open, &rbuf[8]);
	put_unaligned_be32(args->dev->zac_zones_optimal_nonseq, &rbuf[12]);
	put_unaligned_be32(args->dev->zac_zones_max_open, &rbuf[16]);

	return 0;
}