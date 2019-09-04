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
struct TYPE_3__ {int /*<<< orphan*/  vtoc; } ;
union label_t {TYPE_1__ vol; } ;
typedef  int /*<<< orphan*/  tmp ;
struct TYPE_4__ {int /*<<< orphan*/  ulimit; int /*<<< orphan*/  llimit; } ;
struct vtoc_format1_label {scalar_t__ DS1FMTID; TYPE_2__ DS1EXT1; } ;
struct parsed_partitions {int limit; int /*<<< orphan*/  pp_buf; } ;
struct hd_geometry {int sectors; } ;
typedef  int sector_t ;
typedef  int loff_t ;
typedef  int /*<<< orphan*/  Sector ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 scalar_t__* _ascebc ; 
 int cchh2blk (int /*<<< orphan*/ *,struct hd_geometry*) ; 
 int cchhb2blk (int /*<<< orphan*/ *,struct hd_geometry*) ; 
 int /*<<< orphan*/  memcpy (struct vtoc_format1_label*,unsigned char*,int) ; 
 int /*<<< orphan*/  put_dev_sector (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_partition (struct parsed_partitions*,int,int,int) ; 
 unsigned char* read_part_sector (struct parsed_partitions*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 
 int /*<<< orphan*/  strlcat (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int find_vol1_partitions(struct parsed_partitions *state,
				struct hd_geometry *geo,
				int blocksize,
				char name[],
				union label_t *label)
{
	sector_t blk;
	int counter;
	char tmp[64];
	Sector sect;
	unsigned char *data;
	loff_t offset, size;
	struct vtoc_format1_label f1;
	int secperblk;

	snprintf(tmp, sizeof(tmp), "VOL1/%8s:", name);
	strlcat(state->pp_buf, tmp, PAGE_SIZE);
	/*
	 * get start of VTOC from the disk label and then search for format1
	 * and format8 labels
	 */
	secperblk = blocksize >> 9;
	blk = cchhb2blk(&label->vol.vtoc, geo) + 1;
	counter = 0;
	data = read_part_sector(state, blk * secperblk, &sect);
	while (data != NULL) {
		memcpy(&f1, data, sizeof(struct vtoc_format1_label));
		put_dev_sector(sect);
		/* skip FMT4 / FMT5 / FMT7 labels */
		if (f1.DS1FMTID == _ascebc['4']
		    || f1.DS1FMTID == _ascebc['5']
		    || f1.DS1FMTID == _ascebc['7']
		    || f1.DS1FMTID == _ascebc['9']) {
			blk++;
			data = read_part_sector(state, blk * secperblk, &sect);
			continue;
		}
		/* only FMT1 and 8 labels valid at this point */
		if (f1.DS1FMTID != _ascebc['1'] &&
		    f1.DS1FMTID != _ascebc['8'])
			break;
		/* OK, we got valid partition data */
		offset = cchh2blk(&f1.DS1EXT1.llimit, geo);
		size  = cchh2blk(&f1.DS1EXT1.ulimit, geo) -
			offset + geo->sectors;
		offset *= secperblk;
		size *= secperblk;
		if (counter >= state->limit)
			break;
		put_partition(state, counter + 1, offset, size);
		counter++;
		blk++;
		data = read_part_sector(state, blk * secperblk, &sect);
	}
	strlcat(state->pp_buf, "\n", PAGE_SIZE);

	if (!data)
		return -1;

	return 1;
}