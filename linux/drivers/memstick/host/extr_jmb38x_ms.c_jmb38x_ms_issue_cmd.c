#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct memstick_host {int /*<<< orphan*/  dev; } ;
struct jmb38x_ms_host {int cmd_flags; unsigned int* io_word; scalar_t__ ifmode; scalar_t__ addr; TYPE_3__* req; scalar_t__ timeout_jiffies; int /*<<< orphan*/  timer; TYPE_2__* chip; scalar_t__ io_pos; scalar_t__ block_pos; } ;
struct TYPE_10__ {unsigned int length; } ;
struct TYPE_9__ {int error; int tpc; scalar_t__ data_dir; unsigned int data_len; TYPE_4__ sg; scalar_t__ long_data; scalar_t__ need_card_int; } ;
struct TYPE_8__ {TYPE_1__* pdev; } ;
struct TYPE_7__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ BLOCK ; 
 int BLOCK_COUNT_MASK ; 
 unsigned int BLOCK_SIZE_MASK ; 
 scalar_t__ DMA_ADDRESS ; 
 scalar_t__ DMA_CONTROL ; 
 unsigned int DMA_CONTROL_ENABLE ; 
 int DMA_DATA ; 
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int ENOMEM ; 
 int ETIME ; 
 scalar_t__ HOST_CONTROL ; 
 unsigned int HOST_CONTROL_LED ; 
 scalar_t__ INT_SIGNAL_ENABLE ; 
 scalar_t__ INT_STATUS ; 
 scalar_t__ INT_STATUS_ENABLE ; 
 unsigned int INT_STATUS_FIFO_RRDY ; 
 unsigned int INT_STATUS_FIFO_WRDY ; 
 scalar_t__ MEMSTICK_SERIAL ; 
 scalar_t__ READ ; 
 int REG_DATA ; 
 scalar_t__ STATUS ; 
 unsigned int STATUS_HAS_MEDIA ; 
 scalar_t__ TPC ; 
 unsigned int TPC_DATA_SEL ; 
 unsigned int TPC_DIR ; 
 unsigned int TPC_GET_INT ; 
 scalar_t__ TPC_P0 ; 
 scalar_t__ TPC_P1 ; 
 unsigned int TPC_WAIT_INT ; 
 scalar_t__ WRITE ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,...) ; 
 int dma_map_sg (int /*<<< orphan*/ *,TYPE_4__*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  jmb38x_ms_transfer_data (struct jmb38x_ms_host*) ; 
 struct jmb38x_ms_host* memstick_priv (struct memstick_host*) ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  no_dma ; 
 unsigned int readl (scalar_t__) ; 
 unsigned int sg_dma_address (TYPE_4__*) ; 
 unsigned int sg_dma_len (TYPE_4__*) ; 
 int /*<<< orphan*/  writel (unsigned int,scalar_t__) ; 

__attribute__((used)) static int jmb38x_ms_issue_cmd(struct memstick_host *msh)
{
	struct jmb38x_ms_host *host = memstick_priv(msh);
	unsigned int data_len, cmd, t_val;

	if (!(STATUS_HAS_MEDIA & readl(host->addr + STATUS))) {
		dev_dbg(&msh->dev, "no media status\n");
		host->req->error = -ETIME;
		return host->req->error;
	}

	dev_dbg(&msh->dev, "control %08x\n", readl(host->addr + HOST_CONTROL));
	dev_dbg(&msh->dev, "status %08x\n", readl(host->addr + INT_STATUS));
	dev_dbg(&msh->dev, "hstatus %08x\n", readl(host->addr + STATUS));

	host->cmd_flags = 0;
	host->block_pos = 0;
	host->io_pos = 0;
	host->io_word[0] = 0;
	host->io_word[1] = 0;

	cmd = host->req->tpc << 16;
	cmd |= TPC_DATA_SEL;

	if (host->req->data_dir == READ)
		cmd |= TPC_DIR;

	if (host->req->need_card_int) {
		if (host->ifmode == MEMSTICK_SERIAL)
			cmd |= TPC_GET_INT;
		else
			cmd |= TPC_WAIT_INT;
	}

	if (!no_dma)
		host->cmd_flags |= DMA_DATA;

	if (host->req->long_data) {
		data_len = host->req->sg.length;
	} else {
		data_len = host->req->data_len;
		host->cmd_flags &= ~DMA_DATA;
	}

	if (data_len <= 8) {
		cmd &= ~(TPC_DATA_SEL | 0xf);
		host->cmd_flags |= REG_DATA;
		cmd |= data_len & 0xf;
		host->cmd_flags &= ~DMA_DATA;
	}

	if (host->cmd_flags & DMA_DATA) {
		if (1 != dma_map_sg(&host->chip->pdev->dev, &host->req->sg, 1,
				    host->req->data_dir == READ
				    ? DMA_FROM_DEVICE
				    : DMA_TO_DEVICE)) {
			host->req->error = -ENOMEM;
			return host->req->error;
		}
		data_len = sg_dma_len(&host->req->sg);
		writel(sg_dma_address(&host->req->sg),
		       host->addr + DMA_ADDRESS);
		writel(((1 << 16) & BLOCK_COUNT_MASK)
		       | (data_len & BLOCK_SIZE_MASK),
		       host->addr + BLOCK);
		writel(DMA_CONTROL_ENABLE, host->addr + DMA_CONTROL);
	} else if (!(host->cmd_flags & REG_DATA)) {
		writel(((1 << 16) & BLOCK_COUNT_MASK)
		       | (data_len & BLOCK_SIZE_MASK),
		       host->addr + BLOCK);
			t_val = readl(host->addr + INT_STATUS_ENABLE);
			t_val |= host->req->data_dir == READ
				 ? INT_STATUS_FIFO_RRDY
				 : INT_STATUS_FIFO_WRDY;

			writel(t_val, host->addr + INT_STATUS_ENABLE);
			writel(t_val, host->addr + INT_SIGNAL_ENABLE);
	} else {
		cmd &= ~(TPC_DATA_SEL | 0xf);
		host->cmd_flags |= REG_DATA;
		cmd |= data_len & 0xf;

		if (host->req->data_dir == WRITE) {
			jmb38x_ms_transfer_data(host);
			writel(host->io_word[0], host->addr + TPC_P0);
			writel(host->io_word[1], host->addr + TPC_P1);
		}
	}

	mod_timer(&host->timer, jiffies + host->timeout_jiffies);
	writel(HOST_CONTROL_LED | readl(host->addr + HOST_CONTROL),
	       host->addr + HOST_CONTROL);
	host->req->error = 0;

	writel(cmd, host->addr + TPC);
	dev_dbg(&msh->dev, "executing TPC %08x, len %x\n", cmd, data_len);

	return 0;
}