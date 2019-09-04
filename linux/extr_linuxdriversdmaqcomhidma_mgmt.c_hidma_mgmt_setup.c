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
struct hidma_mgmt_dev {int max_write_request; int max_read_request; int max_wr_xactions; int max_rd_xactions; unsigned int dma_channels; int* priority; int* weight; int hw_version; int hw_version_major; int hw_version_minor; int chreset_timeout_cycles; TYPE_1__* pdev; scalar_t__ virtaddr; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int HIDMA_CHRESET_TIMEOUT_MASK ; 
 scalar_t__ HIDMA_CHRESET_TIMEOUT_OFFSET ; 
 scalar_t__ HIDMA_HW_VERSION_OFFSET ; 
 int HIDMA_MAX_BUS_REQ_LEN_MASK ; 
 scalar_t__ HIDMA_MAX_BUS_REQ_LEN_OFFSET ; 
 int HIDMA_MAX_BUS_WR_REQ_BIT_POS ; 
 int HIDMA_MAX_CHANNEL_WEIGHT ; 
 int HIDMA_MAX_RD_XACTIONS_MASK ; 
 int HIDMA_MAX_WR_XACTIONS_BIT_POS ; 
 int HIDMA_MAX_WR_XACTIONS_MASK ; 
 scalar_t__ HIDMA_MAX_XACTIONS_OFFSET ; 
 int HIDMA_PRIORITY_BIT_POS ; 
 scalar_t__ HIDMA_QOS_N_OFFSET ; 
 int HIDMA_WEIGHT_MASK ; 
 int HIDMA_WRR_BIT_POS ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  is_power_of_2 (int) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_mark_last_busy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_put_autosuspend (int /*<<< orphan*/ *) ; 
 void* readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

int hidma_mgmt_setup(struct hidma_mgmt_dev *mgmtdev)
{
	unsigned int i;
	u32 val;

	if (!is_power_of_2(mgmtdev->max_write_request) ||
	    (mgmtdev->max_write_request < 128) ||
	    (mgmtdev->max_write_request > 1024)) {
		dev_err(&mgmtdev->pdev->dev, "invalid write request %d\n",
			mgmtdev->max_write_request);
		return -EINVAL;
	}

	if (!is_power_of_2(mgmtdev->max_read_request) ||
	    (mgmtdev->max_read_request < 128) ||
	    (mgmtdev->max_read_request > 1024)) {
		dev_err(&mgmtdev->pdev->dev, "invalid read request %d\n",
			mgmtdev->max_read_request);
		return -EINVAL;
	}

	if (mgmtdev->max_wr_xactions > HIDMA_MAX_WR_XACTIONS_MASK) {
		dev_err(&mgmtdev->pdev->dev,
			"max_wr_xactions cannot be bigger than %ld\n",
			HIDMA_MAX_WR_XACTIONS_MASK);
		return -EINVAL;
	}

	if (mgmtdev->max_rd_xactions > HIDMA_MAX_RD_XACTIONS_MASK) {
		dev_err(&mgmtdev->pdev->dev,
			"max_rd_xactions cannot be bigger than %ld\n",
			HIDMA_MAX_RD_XACTIONS_MASK);
		return -EINVAL;
	}

	for (i = 0; i < mgmtdev->dma_channels; i++) {
		if (mgmtdev->priority[i] > 1) {
			dev_err(&mgmtdev->pdev->dev,
				"priority can be 0 or 1\n");
			return -EINVAL;
		}

		if (mgmtdev->weight[i] > HIDMA_MAX_CHANNEL_WEIGHT) {
			dev_err(&mgmtdev->pdev->dev,
				"max value of weight can be %d.\n",
				HIDMA_MAX_CHANNEL_WEIGHT);
			return -EINVAL;
		}

		/* weight needs to be at least one */
		if (mgmtdev->weight[i] == 0)
			mgmtdev->weight[i] = 1;
	}

	pm_runtime_get_sync(&mgmtdev->pdev->dev);
	val = readl(mgmtdev->virtaddr + HIDMA_MAX_BUS_REQ_LEN_OFFSET);
	val &= ~(HIDMA_MAX_BUS_REQ_LEN_MASK << HIDMA_MAX_BUS_WR_REQ_BIT_POS);
	val |= mgmtdev->max_write_request << HIDMA_MAX_BUS_WR_REQ_BIT_POS;
	val &= ~HIDMA_MAX_BUS_REQ_LEN_MASK;
	val |= mgmtdev->max_read_request;
	writel(val, mgmtdev->virtaddr + HIDMA_MAX_BUS_REQ_LEN_OFFSET);

	val = readl(mgmtdev->virtaddr + HIDMA_MAX_XACTIONS_OFFSET);
	val &= ~(HIDMA_MAX_WR_XACTIONS_MASK << HIDMA_MAX_WR_XACTIONS_BIT_POS);
	val |= mgmtdev->max_wr_xactions << HIDMA_MAX_WR_XACTIONS_BIT_POS;
	val &= ~HIDMA_MAX_RD_XACTIONS_MASK;
	val |= mgmtdev->max_rd_xactions;
	writel(val, mgmtdev->virtaddr + HIDMA_MAX_XACTIONS_OFFSET);

	mgmtdev->hw_version =
	    readl(mgmtdev->virtaddr + HIDMA_HW_VERSION_OFFSET);
	mgmtdev->hw_version_major = (mgmtdev->hw_version >> 28) & 0xF;
	mgmtdev->hw_version_minor = (mgmtdev->hw_version >> 16) & 0xF;

	for (i = 0; i < mgmtdev->dma_channels; i++) {
		u32 weight = mgmtdev->weight[i];
		u32 priority = mgmtdev->priority[i];

		val = readl(mgmtdev->virtaddr + HIDMA_QOS_N_OFFSET + (4 * i));
		val &= ~(1 << HIDMA_PRIORITY_BIT_POS);
		val |= (priority & 0x1) << HIDMA_PRIORITY_BIT_POS;
		val &= ~(HIDMA_WEIGHT_MASK << HIDMA_WRR_BIT_POS);
		val |= (weight & HIDMA_WEIGHT_MASK) << HIDMA_WRR_BIT_POS;
		writel(val, mgmtdev->virtaddr + HIDMA_QOS_N_OFFSET + (4 * i));
	}

	val = readl(mgmtdev->virtaddr + HIDMA_CHRESET_TIMEOUT_OFFSET);
	val &= ~HIDMA_CHRESET_TIMEOUT_MASK;
	val |= mgmtdev->chreset_timeout_cycles & HIDMA_CHRESET_TIMEOUT_MASK;
	writel(val, mgmtdev->virtaddr + HIDMA_CHRESET_TIMEOUT_OFFSET);

	pm_runtime_mark_last_busy(&mgmtdev->pdev->dev);
	pm_runtime_put_autosuspend(&mgmtdev->pdev->dev);
	return 0;
}