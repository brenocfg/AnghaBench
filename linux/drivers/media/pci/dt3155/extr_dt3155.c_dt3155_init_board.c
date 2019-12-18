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
typedef  scalar_t__ u8 ;
struct pci_dev {int dummy; } ;
struct dt3155_priv {int config; scalar_t__ regs; struct pci_dev* pdev; } ;

/* Variables and functions */
 int ADDR_ERR_EVEN ; 
 int ADDR_ERR_ODD ; 
 int /*<<< orphan*/  AD_ADDR ; 
 int /*<<< orphan*/  AD_CMD ; 
 int AD_CMD_REG ; 
 int /*<<< orphan*/  AD_LUT ; 
 int AD_NEG_REF ; 
 int AD_POS_REF ; 
 int /*<<< orphan*/  CONFIG ; 
 scalar_t__ CSR1 ; 
 scalar_t__ DT3155_ID ; 
 int /*<<< orphan*/  DT_ID ; 
 int ENODEV ; 
 scalar_t__ EVEN_FLD_MASK ; 
 scalar_t__ EVEN_PIXEL_FMT ; 
 int FIFO_EN ; 
 scalar_t__ FIFO_FLAG_CNT ; 
 scalar_t__ FIFO_TRIGER ; 
 int FLD_CRPT_EVEN ; 
 int FLD_CRPT_ODD ; 
 int FLD_DN_EVEN ; 
 int FLD_DN_ODD ; 
 int FLD_END_EVEN ; 
 int FLD_END_ODD ; 
 int FLD_START ; 
 scalar_t__ IIC_CLK_DUR ; 
 scalar_t__ INT_CSR ; 
 scalar_t__ MASK_LENGTH ; 
 scalar_t__ ODD_FLD_MASK ; 
 scalar_t__ ODD_PIXEL_FMT ; 
 int /*<<< orphan*/  PM_LUT_ADDR ; 
 int /*<<< orphan*/  PM_LUT_DATA ; 
 int PM_LUT_PGM ; 
 int PM_LUT_SEL ; 
 scalar_t__ RETRY_WAIT_CNT ; 
 int SRST ; 
 int SYNC_CNL_1 ; 
 int SYNC_LVL_3 ; 
 int VIDEO_CNL_1 ; 
 scalar_t__ XFER_MODE ; 
 int /*<<< orphan*/  iowrite32 (int,scalar_t__) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  pci_set_master (struct pci_dev*) ; 
 int /*<<< orphan*/  read_i2c_reg (scalar_t__,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  write_i2c_reg (scalar_t__,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int dt3155_init_board(struct dt3155_priv *pd)
{
	struct pci_dev *pdev = pd->pdev;
	int i;
	u8 tmp = 0;

	pci_set_master(pdev); /* dt3155 needs it */

	/*  resetting the adapter  */
	iowrite32(ADDR_ERR_ODD | ADDR_ERR_EVEN | FLD_CRPT_ODD | FLD_CRPT_EVEN |
			FLD_DN_ODD | FLD_DN_EVEN, pd->regs + CSR1);
	msleep(20);

	/*  initializing adapter registers  */
	iowrite32(FIFO_EN | SRST, pd->regs + CSR1);
	iowrite32(0xEEEEEE01, pd->regs + EVEN_PIXEL_FMT);
	iowrite32(0xEEEEEE01, pd->regs + ODD_PIXEL_FMT);
	iowrite32(0x00000020, pd->regs + FIFO_TRIGER);
	iowrite32(0x00000103, pd->regs + XFER_MODE);
	iowrite32(0, pd->regs + RETRY_WAIT_CNT);
	iowrite32(0, pd->regs + INT_CSR);
	iowrite32(1, pd->regs + EVEN_FLD_MASK);
	iowrite32(1, pd->regs + ODD_FLD_MASK);
	iowrite32(0, pd->regs + MASK_LENGTH);
	iowrite32(0x0005007C, pd->regs + FIFO_FLAG_CNT);
	iowrite32(0x01010101, pd->regs + IIC_CLK_DUR);

	/* verifying that we have a DT3155 board (not just a SAA7116 chip) */
	read_i2c_reg(pd->regs, DT_ID, &tmp);
	if (tmp != DT3155_ID)
		return -ENODEV;

	/* initialize AD LUT */
	write_i2c_reg(pd->regs, AD_ADDR, 0);
	for (i = 0; i < 256; i++)
		write_i2c_reg(pd->regs, AD_LUT, i);

	/* initialize ADC references */
	/* FIXME: pos_ref & neg_ref depend on VT_50HZ */
	write_i2c_reg(pd->regs, AD_ADDR, AD_CMD_REG);
	write_i2c_reg(pd->regs, AD_CMD, VIDEO_CNL_1 | SYNC_CNL_1 | SYNC_LVL_3);
	write_i2c_reg(pd->regs, AD_ADDR, AD_POS_REF);
	write_i2c_reg(pd->regs, AD_CMD, 34);
	write_i2c_reg(pd->regs, AD_ADDR, AD_NEG_REF);
	write_i2c_reg(pd->regs, AD_CMD, 0);

	/* initialize PM LUT */
	write_i2c_reg(pd->regs, CONFIG, pd->config | PM_LUT_PGM);
	for (i = 0; i < 256; i++) {
		write_i2c_reg(pd->regs, PM_LUT_ADDR, i);
		write_i2c_reg(pd->regs, PM_LUT_DATA, i);
	}
	write_i2c_reg(pd->regs, CONFIG, pd->config | PM_LUT_PGM | PM_LUT_SEL);
	for (i = 0; i < 256; i++) {
		write_i2c_reg(pd->regs, PM_LUT_ADDR, i);
		write_i2c_reg(pd->regs, PM_LUT_DATA, i);
	}
	write_i2c_reg(pd->regs, CONFIG, pd->config); /*  ACQ_MODE_EVEN  */

	/* select channel 1 for input and set sync level */
	write_i2c_reg(pd->regs, AD_ADDR, AD_CMD_REG);
	write_i2c_reg(pd->regs, AD_CMD, VIDEO_CNL_1 | SYNC_CNL_1 | SYNC_LVL_3);

	/* disable all irqs, clear all irq flags */
	iowrite32(FLD_START | FLD_END_EVEN | FLD_END_ODD,
			pd->regs + INT_CSR);

	return 0;
}