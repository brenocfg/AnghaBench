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
struct TYPE_2__ {int block_size; int disk_offset; int block_count; } ;
union label_t {TYPE_1__ cms; } ;
typedef  int /*<<< orphan*/  tmp ;
struct parsed_partitions {int /*<<< orphan*/  pp_buf; } ;
struct hd_geometry {int dummy; } ;
typedef  int sector_t ;
typedef  int loff_t ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  put_partition (struct parsed_partitions*,int,int,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 
 int /*<<< orphan*/  strlcat (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int find_cms1_partitions(struct parsed_partitions *state,
				struct hd_geometry *geo,
				int blocksize,
				char name[],
				union label_t *label,
				sector_t labelsect)
{
	loff_t offset, size;
	char tmp[64];
	int secperblk;

	/*
	 * VM style CMS1 labeled disk
	 */
	blocksize = label->cms.block_size;
	secperblk = blocksize >> 9;
	if (label->cms.disk_offset != 0) {
		snprintf(tmp, sizeof(tmp), "CMS1/%8s(MDSK):", name);
		strlcat(state->pp_buf, tmp, PAGE_SIZE);
		/* disk is reserved minidisk */
		offset = label->cms.disk_offset * secperblk;
		size = (label->cms.block_count - 1) * secperblk;
	} else {
		snprintf(tmp, sizeof(tmp), "CMS1/%8s:", name);
		strlcat(state->pp_buf, tmp, PAGE_SIZE);
		/*
		 * Special case for FBA devices:
		 * If an FBA device is CMS formatted with blocksize > 512 byte
		 * and the DIAG discipline is used, then the CMS label is found
		 * in sector 1 instead of block 1. However, the partition is
		 * still supposed to start in block 2.
		 */
		if (labelsect == 1)
			offset = 2 * secperblk;
		else
			offset = labelsect + secperblk;
		size = label->cms.block_count * secperblk;
	}

	put_partition(state, 1, offset, size-offset);
	strlcat(state->pp_buf, "\n", PAGE_SIZE);
	return 1;
}