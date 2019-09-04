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
typedef  int uint32_t ;
typedef  int uint16_t ;
struct xadc {int /*<<< orphan*/  completion; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int*) ; 
 int EIO ; 
 int /*<<< orphan*/  HZ ; 
 int XADC_ZYNQ_CFG_DFIFOTH_MASK ; 
 int XADC_ZYNQ_CFG_DFIFOTH_OFFSET ; 
 int XADC_ZYNQ_CMD (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XADC_ZYNQ_CMD_NOP ; 
 int /*<<< orphan*/  XADC_ZYNQ_CMD_READ ; 
 int /*<<< orphan*/  XADC_ZYNQ_INT_DFIFO_GTH ; 
 int /*<<< orphan*/  XADC_ZYNQ_REG_CFG ; 
 int /*<<< orphan*/  XADC_ZYNQ_REG_DFIFO ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int wait_for_completion_interruptible_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xadc_read_reg (struct xadc*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  xadc_write_reg (struct xadc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xadc_zynq_drain_fifo (struct xadc*) ; 
 int /*<<< orphan*/  xadc_zynq_update_intmsk (struct xadc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xadc_zynq_write_fifo (struct xadc*,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int xadc_zynq_read_adc_reg(struct xadc *xadc, unsigned int reg,
	uint16_t *val)
{
	uint32_t cmd[2];
	uint32_t resp, tmp;
	int ret;

	cmd[0] = XADC_ZYNQ_CMD(XADC_ZYNQ_CMD_READ, reg, 0);
	cmd[1] = XADC_ZYNQ_CMD(XADC_ZYNQ_CMD_NOP, 0, 0);

	spin_lock_irq(&xadc->lock);
	xadc_zynq_update_intmsk(xadc, XADC_ZYNQ_INT_DFIFO_GTH,
			XADC_ZYNQ_INT_DFIFO_GTH);
	xadc_zynq_drain_fifo(xadc);
	reinit_completion(&xadc->completion);

	xadc_zynq_write_fifo(xadc, cmd, ARRAY_SIZE(cmd));
	xadc_read_reg(xadc, XADC_ZYNQ_REG_CFG, &tmp);
	tmp &= ~XADC_ZYNQ_CFG_DFIFOTH_MASK;
	tmp |= 1 << XADC_ZYNQ_CFG_DFIFOTH_OFFSET;
	xadc_write_reg(xadc, XADC_ZYNQ_REG_CFG, tmp);

	xadc_zynq_update_intmsk(xadc, XADC_ZYNQ_INT_DFIFO_GTH, 0);
	spin_unlock_irq(&xadc->lock);
	ret = wait_for_completion_interruptible_timeout(&xadc->completion, HZ);
	if (ret == 0)
		ret = -EIO;
	if (ret < 0)
		return ret;

	xadc_read_reg(xadc, XADC_ZYNQ_REG_DFIFO, &resp);
	xadc_read_reg(xadc, XADC_ZYNQ_REG_DFIFO, &resp);

	*val = resp & 0xffff;

	return 0;
}