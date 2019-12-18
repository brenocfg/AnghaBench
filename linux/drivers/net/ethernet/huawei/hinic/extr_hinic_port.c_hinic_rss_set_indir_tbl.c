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
typedef  scalar_t__ u64 ;
typedef  size_t u32 ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct hinic_rss_indirect_tbl {size_t* entry; void* size; void* offset; void* group_index; } ;
struct hinic_hwif {struct pci_dev* pdev; } ;
struct hinic_func_to_io {int /*<<< orphan*/  cmdqs; } ;
struct hinic_hwdev {struct hinic_hwif* hwif; struct hinic_func_to_io func_to_io; } ;
struct hinic_dev {struct hinic_hwdev* hwdev; } ;
struct hinic_cmdq_buf {int size; struct hinic_rss_indirect_tbl* buf; } ;

/* Variables and functions */
 int EFAULT ; 
 int /*<<< orphan*/  HINIC_MOD_L2NIC ; 
 int HINIC_RSS_INDIR_SIZE ; 
 int /*<<< orphan*/  HINIC_UCODE_CMD_SET_RSS_INDIR_TABLE ; 
 void* cpu_to_be32 (size_t) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int hinic_alloc_cmdq_buf (int /*<<< orphan*/ *,struct hinic_cmdq_buf*) ; 
 int hinic_cmdq_direct_resp (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct hinic_cmdq_buf*,scalar_t__*) ; 
 int /*<<< orphan*/  hinic_free_cmdq_buf (int /*<<< orphan*/ *,struct hinic_cmdq_buf*) ; 
 int /*<<< orphan*/  memcpy (size_t*,size_t*,size_t) ; 

int hinic_rss_set_indir_tbl(struct hinic_dev *nic_dev, u32 tmpl_idx,
			    const u32 *indir_table)
{
	struct hinic_rss_indirect_tbl *indir_tbl;
	struct hinic_func_to_io *func_to_io;
	struct hinic_cmdq_buf cmd_buf;
	struct hinic_hwdev *hwdev;
	struct hinic_hwif *hwif;
	struct pci_dev *pdev;
	u32 indir_size;
	u64 out_param;
	int err, i;
	u32 *temp;

	hwdev = nic_dev->hwdev;
	func_to_io = &hwdev->func_to_io;
	hwif = hwdev->hwif;
	pdev = hwif->pdev;

	err = hinic_alloc_cmdq_buf(&func_to_io->cmdqs, &cmd_buf);
	if (err) {
		dev_err(&pdev->dev, "Failed to allocate cmdq buf\n");
		return err;
	}

	cmd_buf.size = sizeof(*indir_tbl);

	indir_tbl = cmd_buf.buf;
	indir_tbl->group_index = cpu_to_be32(tmpl_idx);

	for (i = 0; i < HINIC_RSS_INDIR_SIZE; i++) {
		indir_tbl->entry[i] = indir_table[i];

		if (0x3 == (i & 0x3)) {
			temp = (u32 *)&indir_tbl->entry[i - 3];
			*temp = cpu_to_be32(*temp);
		}
	}

	/* cfg the rss indirect table by command queue */
	indir_size = HINIC_RSS_INDIR_SIZE / 2;
	indir_tbl->offset = 0;
	indir_tbl->size = cpu_to_be32(indir_size);

	err = hinic_cmdq_direct_resp(&func_to_io->cmdqs, HINIC_MOD_L2NIC,
				     HINIC_UCODE_CMD_SET_RSS_INDIR_TABLE,
				     &cmd_buf, &out_param);
	if (err || out_param != 0) {
		dev_err(&pdev->dev, "Failed to set rss indir table\n");
		err = -EFAULT;
		goto free_buf;
	}

	indir_tbl->offset = cpu_to_be32(indir_size);
	indir_tbl->size = cpu_to_be32(indir_size);
	memcpy(&indir_tbl->entry[0], &indir_tbl->entry[indir_size], indir_size);

	err = hinic_cmdq_direct_resp(&func_to_io->cmdqs, HINIC_MOD_L2NIC,
				     HINIC_UCODE_CMD_SET_RSS_INDIR_TABLE,
				     &cmd_buf, &out_param);
	if (err || out_param != 0) {
		dev_err(&pdev->dev, "Failed to set rss indir table\n");
		err = -EFAULT;
	}

free_buf:
	hinic_free_cmdq_buf(&func_to_io->cmdqs, &cmd_buf);

	return err;
}