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
struct TYPE_3__ {int block_size; } ;
struct se_device {TYPE_1__ dev_attrib; } ;
struct se_cmd {int t_task_lba; int t_data_nents; TYPE_2__* t_data_sg; struct se_device* se_dev; scalar_t__ prot_op; } ;
struct iov_iter {int dummy; } ;
struct fd_dev {int /*<<< orphan*/  fd_file; } ;
struct bio_vec {scalar_t__ bv_len; int /*<<< orphan*/  bv_offset; int /*<<< orphan*/  bv_page; } ;
typedef  unsigned int ssize_t ;
typedef  int /*<<< orphan*/  sense_reason_t ;
typedef  unsigned int sector_t ;
typedef  int loff_t ;
struct TYPE_4__ {scalar_t__ length; int /*<<< orphan*/  offset; } ;

/* Variables and functions */
 struct fd_dev* FD_DEV (struct se_device*) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  READ ; 
 int /*<<< orphan*/  SAM_STAT_GOOD ; 
 int /*<<< orphan*/  TCM_INVALID_CDB_FIELD ; 
 int /*<<< orphan*/  TCM_LOGICAL_UNIT_COMMUNICATION_FAILURE ; 
 int /*<<< orphan*/  iov_iter_bvec (struct iov_iter*,int /*<<< orphan*/ ,struct bio_vec*,unsigned int,unsigned int) ; 
 struct bio_vec* kcalloc (unsigned int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct bio_vec*) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 unsigned int sbc_get_write_same_sectors (struct se_cmd*) ; 
 int /*<<< orphan*/  sg_page (TYPE_2__*) ; 
 int /*<<< orphan*/  target_complete_cmd (struct se_cmd*,int /*<<< orphan*/ ) ; 
 unsigned int vfs_iter_write (int /*<<< orphan*/ ,struct iov_iter*,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static sense_reason_t
fd_execute_write_same(struct se_cmd *cmd)
{
	struct se_device *se_dev = cmd->se_dev;
	struct fd_dev *fd_dev = FD_DEV(se_dev);
	loff_t pos = cmd->t_task_lba * se_dev->dev_attrib.block_size;
	sector_t nolb = sbc_get_write_same_sectors(cmd);
	struct iov_iter iter;
	struct bio_vec *bvec;
	unsigned int len = 0, i;
	ssize_t ret;

	if (!nolb) {
		target_complete_cmd(cmd, SAM_STAT_GOOD);
		return 0;
	}
	if (cmd->prot_op) {
		pr_err("WRITE_SAME: Protection information with FILEIO"
		       " backends not supported\n");
		return TCM_LOGICAL_UNIT_COMMUNICATION_FAILURE;
	}

	if (cmd->t_data_nents > 1 ||
	    cmd->t_data_sg[0].length != cmd->se_dev->dev_attrib.block_size) {
		pr_err("WRITE_SAME: Illegal SGL t_data_nents: %u length: %u"
			" block_size: %u\n",
			cmd->t_data_nents,
			cmd->t_data_sg[0].length,
			cmd->se_dev->dev_attrib.block_size);
		return TCM_INVALID_CDB_FIELD;
	}

	bvec = kcalloc(nolb, sizeof(struct bio_vec), GFP_KERNEL);
	if (!bvec)
		return TCM_LOGICAL_UNIT_COMMUNICATION_FAILURE;

	for (i = 0; i < nolb; i++) {
		bvec[i].bv_page = sg_page(&cmd->t_data_sg[0]);
		bvec[i].bv_len = cmd->t_data_sg[0].length;
		bvec[i].bv_offset = cmd->t_data_sg[0].offset;

		len += se_dev->dev_attrib.block_size;
	}

	iov_iter_bvec(&iter, READ, bvec, nolb, len);
	ret = vfs_iter_write(fd_dev->fd_file, &iter, &pos, 0);

	kfree(bvec);
	if (ret < 0 || ret != len) {
		pr_err("vfs_iter_write() returned %zd for write same\n", ret);
		return TCM_LOGICAL_UNIT_COMMUNICATION_FAILURE;
	}

	target_complete_cmd(cmd, SAM_STAT_GOOD);
	return 0;
}