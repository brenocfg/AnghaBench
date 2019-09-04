#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int ldl_version; int formatted_blocks; } ;
union label_t {TYPE_1__ lnx; } ;
typedef  int /*<<< orphan*/  tmp ;
struct parsed_partitions {int /*<<< orphan*/  pp_buf; } ;
struct hd_geometry {int cylinders; int heads; int sectors; } ;
typedef  int sector_t ;
typedef  int loff_t ;
struct TYPE_5__ {int /*<<< orphan*/  type; } ;
typedef  TYPE_2__ dasd_information2_t ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  put_partition (struct parsed_partitions*,int,int,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strlcat (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int find_lnx1_partitions(struct parsed_partitions *state,
				struct hd_geometry *geo,
				int blocksize,
				char name[],
				union label_t *label,
				sector_t labelsect,
				loff_t i_size,
				dasd_information2_t *info)
{
	loff_t offset, geo_size, size;
	char tmp[64];
	int secperblk;

	snprintf(tmp, sizeof(tmp), "LNX1/%8s:", name);
	strlcat(state->pp_buf, tmp, PAGE_SIZE);
	secperblk = blocksize >> 9;
	if (label->lnx.ldl_version == 0xf2) {
		size = label->lnx.formatted_blocks * secperblk;
	} else {
		/*
		 * Formated w/o large volume support. If the sanity check
		 * 'size based on geo == size based on i_size' is true, then
		 * we can safely assume that we know the formatted size of
		 * the disk, otherwise we need additional information
		 * that we can only get from a real DASD device.
		 */
		geo_size = geo->cylinders * geo->heads
			* geo->sectors * secperblk;
		size = i_size >> 9;
		if (size != geo_size) {
			if (!info) {
				strlcat(state->pp_buf, "\n", PAGE_SIZE);
				return 1;
			}
			if (!strcmp(info->type, "ECKD"))
				if (geo_size < size)
					size = geo_size;
			/* else keep size based on i_size */
		}
	}
	/* first and only partition starts in the first block after the label */
	offset = labelsect + secperblk;
	put_partition(state, 1, offset, size - offset);
	strlcat(state->pp_buf, "\n", PAGE_SIZE);
	return 1;
}