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
typedef  int u32 ;
struct TYPE_2__ {int block_size; scalar_t__ pi_prot_type; scalar_t__ pi_prot_verify; } ;
struct se_device {int prot_length; TYPE_1__ dev_attrib; } ;
struct se_cmd {int t_prot_nents; int prot_length; int data_length; int t_task_lba; int se_cmd_flags; struct scatterlist* t_prot_sg; scalar_t__ prot_type; struct se_device* se_dev; } ;
struct scatterlist {int dummy; } ;
struct file {int dummy; } ;
struct fd_dev {struct file* fd_file; struct file* fd_prot_file; } ;
typedef  int /*<<< orphan*/  sense_reason_t ;
typedef  int loff_t ;
typedef  enum dma_data_direction { ____Placeholder_dma_data_direction } dma_data_direction ;

/* Variables and functions */
 int DMA_FROM_DEVICE ; 
 struct fd_dev* FD_DEV (struct se_device*) ; 
 int LLONG_MAX ; 
 int /*<<< orphan*/  SAM_STAT_GOOD ; 
 int SCF_FUA ; 
 int /*<<< orphan*/  TCM_LOGICAL_UNIT_COMMUNICATION_FAILURE ; 
 int fd_do_rw (struct se_cmd*,struct file*,int,struct scatterlist*,int,int,int) ; 
 int ilog2 (int) ; 
 int /*<<< orphan*/  sbc_dif_verify (struct se_cmd*,int,int,int /*<<< orphan*/ ,struct scatterlist*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  target_complete_cmd (struct se_cmd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfs_fsync_range (struct file*,int,int,int) ; 

__attribute__((used)) static sense_reason_t
fd_execute_rw_buffered(struct se_cmd *cmd, struct scatterlist *sgl, u32 sgl_nents,
	      enum dma_data_direction data_direction)
{
	struct se_device *dev = cmd->se_dev;
	struct fd_dev *fd_dev = FD_DEV(dev);
	struct file *file = fd_dev->fd_file;
	struct file *pfile = fd_dev->fd_prot_file;
	sense_reason_t rc;
	int ret = 0;
	/*
	 * Call vectorized fileio functions to map struct scatterlist
	 * physical memory addresses to struct iovec virtual memory.
	 */
	if (data_direction == DMA_FROM_DEVICE) {
		if (cmd->prot_type && dev->dev_attrib.pi_prot_type) {
			ret = fd_do_rw(cmd, pfile, dev->prot_length,
				       cmd->t_prot_sg, cmd->t_prot_nents,
				       cmd->prot_length, 0);
			if (ret < 0)
				return TCM_LOGICAL_UNIT_COMMUNICATION_FAILURE;
		}

		ret = fd_do_rw(cmd, file, dev->dev_attrib.block_size,
			       sgl, sgl_nents, cmd->data_length, 0);

		if (ret > 0 && cmd->prot_type && dev->dev_attrib.pi_prot_type &&
		    dev->dev_attrib.pi_prot_verify) {
			u32 sectors = cmd->data_length >>
					ilog2(dev->dev_attrib.block_size);

			rc = sbc_dif_verify(cmd, cmd->t_task_lba, sectors,
					    0, cmd->t_prot_sg, 0);
			if (rc)
				return rc;
		}
	} else {
		if (cmd->prot_type && dev->dev_attrib.pi_prot_type &&
		    dev->dev_attrib.pi_prot_verify) {
			u32 sectors = cmd->data_length >>
					ilog2(dev->dev_attrib.block_size);

			rc = sbc_dif_verify(cmd, cmd->t_task_lba, sectors,
					    0, cmd->t_prot_sg, 0);
			if (rc)
				return rc;
		}

		ret = fd_do_rw(cmd, file, dev->dev_attrib.block_size,
			       sgl, sgl_nents, cmd->data_length, 1);
		/*
		 * Perform implicit vfs_fsync_range() for fd_do_writev() ops
		 * for SCSI WRITEs with Forced Unit Access (FUA) set.
		 * Allow this to happen independent of WCE=0 setting.
		 */
		if (ret > 0 && (cmd->se_cmd_flags & SCF_FUA)) {
			loff_t start = cmd->t_task_lba *
				dev->dev_attrib.block_size;
			loff_t end;

			if (cmd->data_length)
				end = start + cmd->data_length - 1;
			else
				end = LLONG_MAX;

			vfs_fsync_range(fd_dev->fd_file, start, end, 1);
		}

		if (ret > 0 && cmd->prot_type && dev->dev_attrib.pi_prot_type) {
			ret = fd_do_rw(cmd, pfile, dev->prot_length,
				       cmd->t_prot_sg, cmd->t_prot_nents,
				       cmd->prot_length, 1);
			if (ret < 0)
				return TCM_LOGICAL_UNIT_COMMUNICATION_FAILURE;
		}
	}

	if (ret < 0)
		return TCM_LOGICAL_UNIT_COMMUNICATION_FAILURE;

	target_complete_cmd(cmd, SAM_STAT_GOOD);
	return 0;
}