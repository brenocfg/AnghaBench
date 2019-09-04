#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct st_fdma_dev {int /*<<< orphan*/  dev; } ;
struct TYPE_8__ {int dir; int /*<<< orphan*/  req_ctrl; scalar_t__ dev_addr; } ;
struct TYPE_7__ {int src_addr_width; int dst_addr_width; scalar_t__ dst_addr; scalar_t__ dst_maxburst; scalar_t__ src_addr; scalar_t__ src_maxburst; } ;
struct TYPE_5__ {int chan_id; } ;
struct TYPE_6__ {TYPE_1__ chan; } ;
struct st_fdma_chan {TYPE_4__ cfg; TYPE_3__ scfg; struct st_fdma_dev* fdev; TYPE_2__ vchan; } ;
typedef  enum dma_transfer_direction { ____Placeholder_dma_transfer_direction } dma_transfer_direction ;
typedef  enum dma_slave_buswidth { ____Placeholder_dma_slave_buswidth } dma_slave_buswidth ;

/* Variables and functions */
#define  DMA_DEV_TO_MEM 133 
#define  DMA_MEM_TO_DEV 132 
#define  DMA_SLAVE_BUSWIDTH_1_BYTE 131 
#define  DMA_SLAVE_BUSWIDTH_2_BYTES 130 
#define  DMA_SLAVE_BUSWIDTH_4_BYTES 129 
#define  DMA_SLAVE_BUSWIDTH_8_BYTES 128 
 int EINVAL ; 
 int /*<<< orphan*/  FDMA_REQ_CTRL_NUM_OPS (scalar_t__) ; 
 int /*<<< orphan*/  FDMA_REQ_CTRL_NUM_OPS_MASK ; 
 int /*<<< orphan*/  FDMA_REQ_CTRL_OFST ; 
 int /*<<< orphan*/  FDMA_REQ_CTRL_OPCODE_LD_ST1 ; 
 int /*<<< orphan*/  FDMA_REQ_CTRL_OPCODE_LD_ST2 ; 
 int /*<<< orphan*/  FDMA_REQ_CTRL_OPCODE_LD_ST4 ; 
 int /*<<< orphan*/  FDMA_REQ_CTRL_OPCODE_LD_ST8 ; 
 int /*<<< orphan*/  FDMA_REQ_CTRL_OPCODE_MASK ; 
 int /*<<< orphan*/  FDMA_REQ_CTRL_WNR ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dreq_write (struct st_fdma_chan*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int config_reqctrl(struct st_fdma_chan *fchan,
			  enum dma_transfer_direction direction)
{
	u32 maxburst = 0, addr = 0;
	enum dma_slave_buswidth width;
	int ch_id = fchan->vchan.chan.chan_id;
	struct st_fdma_dev *fdev = fchan->fdev;

	switch (direction) {

	case DMA_DEV_TO_MEM:
		fchan->cfg.req_ctrl &= ~FDMA_REQ_CTRL_WNR;
		maxburst = fchan->scfg.src_maxburst;
		width = fchan->scfg.src_addr_width;
		addr = fchan->scfg.src_addr;
		break;

	case DMA_MEM_TO_DEV:
		fchan->cfg.req_ctrl |= FDMA_REQ_CTRL_WNR;
		maxburst = fchan->scfg.dst_maxburst;
		width = fchan->scfg.dst_addr_width;
		addr = fchan->scfg.dst_addr;
		break;

	default:
		return -EINVAL;
	}

	fchan->cfg.req_ctrl &= ~FDMA_REQ_CTRL_OPCODE_MASK;

	switch (width) {

	case DMA_SLAVE_BUSWIDTH_1_BYTE:
		fchan->cfg.req_ctrl |= FDMA_REQ_CTRL_OPCODE_LD_ST1;
		break;

	case DMA_SLAVE_BUSWIDTH_2_BYTES:
		fchan->cfg.req_ctrl |= FDMA_REQ_CTRL_OPCODE_LD_ST2;
		break;

	case DMA_SLAVE_BUSWIDTH_4_BYTES:
		fchan->cfg.req_ctrl |= FDMA_REQ_CTRL_OPCODE_LD_ST4;
		break;

	case DMA_SLAVE_BUSWIDTH_8_BYTES:
		fchan->cfg.req_ctrl |= FDMA_REQ_CTRL_OPCODE_LD_ST8;
		break;

	default:
		return -EINVAL;
	}

	fchan->cfg.req_ctrl &= ~FDMA_REQ_CTRL_NUM_OPS_MASK;
	fchan->cfg.req_ctrl |= FDMA_REQ_CTRL_NUM_OPS(maxburst-1);
	dreq_write(fchan, fchan->cfg.req_ctrl, FDMA_REQ_CTRL_OFST);

	fchan->cfg.dev_addr = addr;
	fchan->cfg.dir = direction;

	dev_dbg(fdev->dev, "chan:%d config_reqctrl:%#x req_ctrl:%#lx\n",
		ch_id, addr, fchan->cfg.req_ctrl);

	return 0;
}