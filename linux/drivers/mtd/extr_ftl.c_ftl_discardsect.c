#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct mtd_blktrans_dev {int dummy; } ;
struct TYPE_6__ {int EraseUnitSize; } ;
struct TYPE_7__ {int* VirtualBlockMap; TYPE_1__* EUNInfo; TYPE_2__ header; } ;
typedef  TYPE_3__ partition_t ;
struct TYPE_5__ {int /*<<< orphan*/  Deleted; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  pr_debug (char*,unsigned long,unsigned int) ; 
 scalar_t__ set_bam_entry (TYPE_3__*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ftl_discardsect(struct mtd_blktrans_dev *dev,
			   unsigned long sector, unsigned nr_sects)
{
	partition_t *part = (void *)dev;
	uint32_t bsize = 1 << part->header.EraseUnitSize;

	pr_debug("FTL erase sector %ld for %d sectors\n",
	      sector, nr_sects);

	while (nr_sects) {
		uint32_t old_addr = part->VirtualBlockMap[sector];
		if (old_addr != 0xffffffff) {
			part->VirtualBlockMap[sector] = 0xffffffff;
			part->EUNInfo[old_addr/bsize].Deleted++;
			if (set_bam_entry(part, old_addr, 0))
				return -EIO;
		}
		nr_sects--;
		sector++;
	}

	return 0;
}