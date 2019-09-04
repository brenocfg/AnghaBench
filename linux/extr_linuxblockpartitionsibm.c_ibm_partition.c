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
union label_t {scalar_t__ format; int label_block; } ;
struct parsed_partitions {int /*<<< orphan*/  pp_buf; struct block_device* bdev; } ;
struct hd_geometry {scalar_t__ format; int label_block; } ;
struct block_device {int /*<<< orphan*/  bd_inode; } ;
typedef  int /*<<< orphan*/  sector_t ;
typedef  int loff_t ;
typedef  union label_t dasd_information2_t ;

/* Variables and functions */
 int /*<<< orphan*/  BIODASDINFO2 ; 
 scalar_t__ DASD_FORMAT_LDL ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HDIO_GETGEO ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int bdev_logical_block_size (struct block_device*) ; 
 int find_cms1_partitions (struct parsed_partitions*,union label_t*,int,char*,union label_t*,int /*<<< orphan*/ ) ; 
 scalar_t__ find_label (struct parsed_partitions*,union label_t*,union label_t*,int,int /*<<< orphan*/ *,char*,char*,union label_t*) ; 
 int find_lnx1_partitions (struct parsed_partitions*,union label_t*,int,char*,union label_t*,int /*<<< orphan*/ ,int,union label_t*) ; 
 int find_vol1_partitions (struct parsed_partitions*,union label_t*,int,char*,union label_t*) ; 
 int i_size_read (int /*<<< orphan*/ ) ; 
 scalar_t__ ioctl_by_bdev (struct block_device*,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  kfree (union label_t*) ; 
 union label_t* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_partition (struct parsed_partitions*,int,int,int) ; 
 int /*<<< orphan*/  strlcat (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncmp (char*,char*,int) ; 

int ibm_partition(struct parsed_partitions *state)
{
	struct block_device *bdev = state->bdev;
	int blocksize, res;
	loff_t i_size, offset, size;
	dasd_information2_t *info;
	struct hd_geometry *geo;
	char type[5] = {0,};
	char name[7] = {0,};
	sector_t labelsect;
	union label_t *label;

	res = 0;
	blocksize = bdev_logical_block_size(bdev);
	if (blocksize <= 0)
		goto out_exit;
	i_size = i_size_read(bdev->bd_inode);
	if (i_size == 0)
		goto out_exit;
	info = kmalloc(sizeof(dasd_information2_t), GFP_KERNEL);
	if (info == NULL)
		goto out_exit;
	geo = kmalloc(sizeof(struct hd_geometry), GFP_KERNEL);
	if (geo == NULL)
		goto out_nogeo;
	label = kmalloc(sizeof(union label_t), GFP_KERNEL);
	if (label == NULL)
		goto out_nolab;
	if (ioctl_by_bdev(bdev, HDIO_GETGEO, (unsigned long)geo) != 0)
		goto out_freeall;
	if (ioctl_by_bdev(bdev, BIODASDINFO2, (unsigned long)info) != 0) {
		kfree(info);
		info = NULL;
	}

	if (find_label(state, info, geo, blocksize, &labelsect, name, type,
		       label)) {
		if (!strncmp(type, "VOL1", 4)) {
			res = find_vol1_partitions(state, geo, blocksize, name,
						   label);
		} else if (!strncmp(type, "LNX1", 4)) {
			res = find_lnx1_partitions(state, geo, blocksize, name,
						   label, labelsect, i_size,
						   info);
		} else if (!strncmp(type, "CMS1", 4)) {
			res = find_cms1_partitions(state, geo, blocksize, name,
						   label, labelsect);
		}
	} else if (info) {
		/*
		 * ugly but needed for backward compatibility:
		 * If the block device is a DASD (i.e. BIODASDINFO2 works),
		 * then we claim it in any case, even though it has no valid
		 * label. If it has the LDL format, then we simply define a
		 * partition as if it had an LNX1 label.
		 */
		res = 1;
		if (info->format == DASD_FORMAT_LDL) {
			strlcat(state->pp_buf, "(nonl)", PAGE_SIZE);
			size = i_size >> 9;
			offset = (info->label_block + 1) * (blocksize >> 9);
			put_partition(state, 1, offset, size-offset);
			strlcat(state->pp_buf, "\n", PAGE_SIZE);
		}
	} else
		res = 0;

out_freeall:
	kfree(label);
out_nolab:
	kfree(geo);
out_nogeo:
	kfree(info);
out_exit:
	return res;
}