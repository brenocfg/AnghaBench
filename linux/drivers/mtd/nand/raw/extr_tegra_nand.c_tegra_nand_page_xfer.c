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
typedef  int u32 ;
struct tegra_nand_controller {int /*<<< orphan*/  dev; int /*<<< orphan*/  dma_complete; int /*<<< orphan*/  command_complete; scalar_t__ regs; int /*<<< orphan*/  cur_cs; } ;
struct nand_chip {int options; int /*<<< orphan*/  cur_cs; int /*<<< orphan*/  controller; } ;
struct mtd_info {int writesize; int oobsize; } ;
typedef  enum dma_data_direction { ____Placeholder_dma_data_direction } dma_data_direction ;
typedef  int dma_addr_t ;

/* Variables and functions */
 scalar_t__ ADDR_REG1 ; 
 scalar_t__ ADDR_REG2 ; 
 scalar_t__ CMD_REG1 ; 
 scalar_t__ CMD_REG2 ; 
 scalar_t__ COMMAND ; 
 int COMMAND_AFT_DAT ; 
 int COMMAND_ALE ; 
 int COMMAND_ALE_SIZE (int) ; 
 int COMMAND_A_VALID ; 
 int COMMAND_B_VALID ; 
 int COMMAND_CE (int /*<<< orphan*/ ) ; 
 int COMMAND_CLE ; 
 int COMMAND_GO ; 
 int COMMAND_RBSY_CHK ; 
 int COMMAND_RX ; 
 int COMMAND_SEC_CMD ; 
 int COMMAND_TRANS_SIZE (int) ; 
 int COMMAND_TX ; 
 scalar_t__ DATA_PTR ; 
 scalar_t__ DMA_CFG_A ; 
 scalar_t__ DMA_CFG_B ; 
 int DMA_FROM_DEVICE ; 
 scalar_t__ DMA_MST_CTRL ; 
 int DMA_MST_CTRL_BURST_16 ; 
 int DMA_MST_CTRL_EN_A ; 
 int DMA_MST_CTRL_EN_B ; 
 int DMA_MST_CTRL_GO ; 
 int DMA_MST_CTRL_IE_DONE ; 
 int DMA_MST_CTRL_IN ; 
 int DMA_MST_CTRL_IS_DONE ; 
 int DMA_MST_CTRL_OUT ; 
 int DMA_MST_CTRL_PERF_EN ; 
 int DMA_MST_CTRL_REUSE ; 
 int DMA_TO_DEVICE ; 
 int EINVAL ; 
 int ETIMEDOUT ; 
 int NAND_CMD_PAGEPROG ; 
 int NAND_CMD_READ0 ; 
 int NAND_CMD_READSTART ; 
 int NAND_CMD_SEQIN ; 
 int NAND_ROW_ADDR_3 ; 
 scalar_t__ TAG_PTR ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int dma_map_single (int /*<<< orphan*/ ,void*,int,int) ; 
 int dma_mapping_error (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  tegra_nand_controller_abort (struct tegra_nand_controller*) ; 
 int /*<<< orphan*/  tegra_nand_dump_reg (struct tegra_nand_controller*) ; 
 int /*<<< orphan*/  tegra_nand_select_target (struct nand_chip*,int /*<<< orphan*/ ) ; 
 struct tegra_nand_controller* to_tegra_ctrl (int /*<<< orphan*/ ) ; 
 int wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

__attribute__((used)) static int tegra_nand_page_xfer(struct mtd_info *mtd, struct nand_chip *chip,
				void *buf, void *oob_buf, int oob_len, int page,
				bool read)
{
	struct tegra_nand_controller *ctrl = to_tegra_ctrl(chip->controller);
	enum dma_data_direction dir = read ? DMA_FROM_DEVICE : DMA_TO_DEVICE;
	dma_addr_t dma_addr = 0, dma_addr_oob = 0;
	u32 addr1, cmd, dma_ctrl;
	int ret;

	tegra_nand_select_target(chip, chip->cur_cs);

	if (read) {
		writel_relaxed(NAND_CMD_READ0, ctrl->regs + CMD_REG1);
		writel_relaxed(NAND_CMD_READSTART, ctrl->regs + CMD_REG2);
	} else {
		writel_relaxed(NAND_CMD_SEQIN, ctrl->regs + CMD_REG1);
		writel_relaxed(NAND_CMD_PAGEPROG, ctrl->regs + CMD_REG2);
	}
	cmd = COMMAND_CLE | COMMAND_SEC_CMD;

	/* Lower 16-bits are column, by default 0 */
	addr1 = page << 16;

	if (!buf)
		addr1 |= mtd->writesize;
	writel_relaxed(addr1, ctrl->regs + ADDR_REG1);

	if (chip->options & NAND_ROW_ADDR_3) {
		writel_relaxed(page >> 16, ctrl->regs + ADDR_REG2);
		cmd |= COMMAND_ALE | COMMAND_ALE_SIZE(5);
	} else {
		cmd |= COMMAND_ALE | COMMAND_ALE_SIZE(4);
	}

	if (buf) {
		dma_addr = dma_map_single(ctrl->dev, buf, mtd->writesize, dir);
		ret = dma_mapping_error(ctrl->dev, dma_addr);
		if (ret) {
			dev_err(ctrl->dev, "dma mapping error\n");
			return -EINVAL;
		}

		writel_relaxed(mtd->writesize - 1, ctrl->regs + DMA_CFG_A);
		writel_relaxed(dma_addr, ctrl->regs + DATA_PTR);
	}

	if (oob_buf) {
		dma_addr_oob = dma_map_single(ctrl->dev, oob_buf, mtd->oobsize,
					      dir);
		ret = dma_mapping_error(ctrl->dev, dma_addr_oob);
		if (ret) {
			dev_err(ctrl->dev, "dma mapping error\n");
			ret = -EINVAL;
			goto err_unmap_dma_page;
		}

		writel_relaxed(oob_len - 1, ctrl->regs + DMA_CFG_B);
		writel_relaxed(dma_addr_oob, ctrl->regs + TAG_PTR);
	}

	dma_ctrl = DMA_MST_CTRL_GO | DMA_MST_CTRL_PERF_EN |
		   DMA_MST_CTRL_IE_DONE | DMA_MST_CTRL_IS_DONE |
		   DMA_MST_CTRL_BURST_16;

	if (buf)
		dma_ctrl |= DMA_MST_CTRL_EN_A;
	if (oob_buf)
		dma_ctrl |= DMA_MST_CTRL_EN_B;

	if (read)
		dma_ctrl |= DMA_MST_CTRL_IN | DMA_MST_CTRL_REUSE;
	else
		dma_ctrl |= DMA_MST_CTRL_OUT;

	writel_relaxed(dma_ctrl, ctrl->regs + DMA_MST_CTRL);

	cmd |= COMMAND_GO | COMMAND_RBSY_CHK | COMMAND_TRANS_SIZE(9) |
	       COMMAND_CE(ctrl->cur_cs);

	if (buf)
		cmd |= COMMAND_A_VALID;
	if (oob_buf)
		cmd |= COMMAND_B_VALID;

	if (read)
		cmd |= COMMAND_RX;
	else
		cmd |= COMMAND_TX | COMMAND_AFT_DAT;

	writel_relaxed(cmd, ctrl->regs + COMMAND);

	ret = wait_for_completion_timeout(&ctrl->command_complete,
					  msecs_to_jiffies(500));
	if (!ret) {
		dev_err(ctrl->dev, "COMMAND timeout\n");
		tegra_nand_dump_reg(ctrl);
		tegra_nand_controller_abort(ctrl);
		ret = -ETIMEDOUT;
		goto err_unmap_dma;
	}

	ret = wait_for_completion_timeout(&ctrl->dma_complete,
					  msecs_to_jiffies(500));
	if (!ret) {
		dev_err(ctrl->dev, "DMA timeout\n");
		tegra_nand_dump_reg(ctrl);
		tegra_nand_controller_abort(ctrl);
		ret = -ETIMEDOUT;
		goto err_unmap_dma;
	}
	ret = 0;

err_unmap_dma:
	if (oob_buf)
		dma_unmap_single(ctrl->dev, dma_addr_oob, mtd->oobsize, dir);
err_unmap_dma_page:
	if (buf)
		dma_unmap_single(ctrl->dev, dma_addr, mtd->writesize, dir);

	return ret;
}