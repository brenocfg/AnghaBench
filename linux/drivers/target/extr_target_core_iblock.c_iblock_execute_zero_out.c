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
struct se_device {int dummy; } ;
struct se_cmd {int /*<<< orphan*/  t_task_lba; int /*<<< orphan*/  data_length; struct scatterlist* t_data_sg; struct se_device* se_dev; } ;
struct scatterlist {int offset; } ;
struct block_device {int dummy; } ;
typedef  int /*<<< orphan*/  sense_reason_t ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GOOD ; 
 int /*<<< orphan*/  TCM_LOGICAL_UNIT_COMMUNICATION_FAILURE ; 
 int blkdev_issue_zeroout (struct block_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 unsigned char* kmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kunmap (int /*<<< orphan*/ ) ; 
 unsigned char* memchr_inv (unsigned char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sbc_get_write_same_sectors (struct se_cmd*) ; 
 int /*<<< orphan*/  sg_page (struct scatterlist*) ; 
 int /*<<< orphan*/  target_complete_cmd (struct se_cmd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  target_to_linux_sector (struct se_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static sense_reason_t
iblock_execute_zero_out(struct block_device *bdev, struct se_cmd *cmd)
{
	struct se_device *dev = cmd->se_dev;
	struct scatterlist *sg = &cmd->t_data_sg[0];
	unsigned char *buf, *not_zero;
	int ret;

	buf = kmap(sg_page(sg)) + sg->offset;
	if (!buf)
		return TCM_LOGICAL_UNIT_COMMUNICATION_FAILURE;
	/*
	 * Fall back to block_execute_write_same() slow-path if
	 * incoming WRITE_SAME payload does not contain zeros.
	 */
	not_zero = memchr_inv(buf, 0x00, cmd->data_length);
	kunmap(sg_page(sg));

	if (not_zero)
		return TCM_LOGICAL_UNIT_COMMUNICATION_FAILURE;

	ret = blkdev_issue_zeroout(bdev,
				target_to_linux_sector(dev, cmd->t_task_lba),
				target_to_linux_sector(dev,
					sbc_get_write_same_sectors(cmd)),
				GFP_KERNEL, false);
	if (ret)
		return TCM_LOGICAL_UNIT_COMMUNICATION_FAILURE;

	target_complete_cmd(cmd, GOOD);
	return 0;
}