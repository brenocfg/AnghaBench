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
struct vb2_queue {int dummy; } ;
struct vb2_buffer {int dummy; } ;
struct dt3155_priv {int width; int config; int csr2; scalar_t__ regs; scalar_t__ sequence; TYPE_1__* curr_buf; } ;
typedef  int dma_addr_t ;
struct TYPE_2__ {struct vb2_buffer vb2_buf; } ;

/* Variables and functions */
 int BUSY_EVEN ; 
 int BUSY_ODD ; 
 int CAP_CONT_EVEN ; 
 int CAP_CONT_ODD ; 
 int /*<<< orphan*/  CONFIG ; 
 scalar_t__ CSR1 ; 
 int /*<<< orphan*/  CSR2 ; 
 int CSR_DONE ; 
 int CSR_ERROR ; 
 int /*<<< orphan*/  EVEN_CSR ; 
 scalar_t__ EVEN_DMA_START ; 
 scalar_t__ EVEN_DMA_STRIDE ; 
 int FIFO_EN ; 
 int FLD_CRPT_EVEN ; 
 int FLD_CRPT_ODD ; 
 int FLD_DN_EVEN ; 
 int FLD_DN_ODD ; 
 int FLD_END_EVEN ; 
 int FLD_END_ODD ; 
 int FLD_END_ODD_EN ; 
 int FLD_START ; 
 int FLD_START_EN ; 
 scalar_t__ INT_CSR ; 
 int /*<<< orphan*/  ODD_CSR ; 
 scalar_t__ ODD_DMA_START ; 
 scalar_t__ ODD_DMA_STRIDE ; 
 int SRST ; 
 int /*<<< orphan*/  iowrite32 (int,scalar_t__) ; 
 int vb2_dma_contig_plane_dma_addr (struct vb2_buffer*,int /*<<< orphan*/ ) ; 
 struct dt3155_priv* vb2_get_drv_priv (struct vb2_queue*) ; 
 int /*<<< orphan*/  wait_i2c_reg (scalar_t__) ; 
 int /*<<< orphan*/  write_i2c_reg (scalar_t__,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int dt3155_start_streaming(struct vb2_queue *q, unsigned count)
{
	struct dt3155_priv *pd = vb2_get_drv_priv(q);
	struct vb2_buffer *vb = &pd->curr_buf->vb2_buf;
	dma_addr_t dma_addr;

	pd->sequence = 0;
	dma_addr = vb2_dma_contig_plane_dma_addr(vb, 0);
	iowrite32(dma_addr, pd->regs + EVEN_DMA_START);
	iowrite32(dma_addr + pd->width, pd->regs + ODD_DMA_START);
	iowrite32(pd->width, pd->regs + EVEN_DMA_STRIDE);
	iowrite32(pd->width, pd->regs + ODD_DMA_STRIDE);
	/* enable interrupts, clear all irq flags */
	iowrite32(FLD_START_EN | FLD_END_ODD_EN | FLD_START |
			FLD_END_EVEN | FLD_END_ODD, pd->regs + INT_CSR);
	iowrite32(FIFO_EN | SRST | FLD_CRPT_ODD | FLD_CRPT_EVEN |
		  FLD_DN_ODD | FLD_DN_EVEN | CAP_CONT_EVEN | CAP_CONT_ODD,
							pd->regs + CSR1);
	wait_i2c_reg(pd->regs);
	write_i2c_reg(pd->regs, CONFIG, pd->config);
	write_i2c_reg(pd->regs, EVEN_CSR, CSR_ERROR | CSR_DONE);
	write_i2c_reg(pd->regs, ODD_CSR, CSR_ERROR | CSR_DONE);

	/*  start the board  */
	write_i2c_reg(pd->regs, CSR2, pd->csr2 | BUSY_EVEN | BUSY_ODD);
	return 0;
}