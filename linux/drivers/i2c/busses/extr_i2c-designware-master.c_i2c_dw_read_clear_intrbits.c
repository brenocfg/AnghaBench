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
struct dw_i2c_dev {void* abort_source; } ;

/* Variables and functions */
 int /*<<< orphan*/  DW_IC_CLR_ACTIVITY ; 
 int /*<<< orphan*/  DW_IC_CLR_GEN_CALL ; 
 int /*<<< orphan*/  DW_IC_CLR_RD_REQ ; 
 int /*<<< orphan*/  DW_IC_CLR_RX_DONE ; 
 int /*<<< orphan*/  DW_IC_CLR_RX_OVER ; 
 int /*<<< orphan*/  DW_IC_CLR_RX_UNDER ; 
 int /*<<< orphan*/  DW_IC_CLR_START_DET ; 
 int /*<<< orphan*/  DW_IC_CLR_STOP_DET ; 
 int /*<<< orphan*/  DW_IC_CLR_TX_ABRT ; 
 int /*<<< orphan*/  DW_IC_CLR_TX_OVER ; 
 int DW_IC_INTR_ACTIVITY ; 
 int DW_IC_INTR_GEN_CALL ; 
 int DW_IC_INTR_RD_REQ ; 
 int DW_IC_INTR_RX_DONE ; 
 int DW_IC_INTR_RX_OVER ; 
 int DW_IC_INTR_RX_UNDER ; 
 int DW_IC_INTR_START_DET ; 
 int /*<<< orphan*/  DW_IC_INTR_STAT ; 
 int DW_IC_INTR_STOP_DET ; 
 int DW_IC_INTR_TX_ABRT ; 
 int DW_IC_INTR_TX_OVER ; 
 int /*<<< orphan*/  DW_IC_TX_ABRT_SOURCE ; 
 void* dw_readl (struct dw_i2c_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 i2c_dw_read_clear_intrbits(struct dw_i2c_dev *dev)
{
	u32 stat;

	/*
	 * The IC_INTR_STAT register just indicates "enabled" interrupts.
	 * Ths unmasked raw version of interrupt status bits are available
	 * in the IC_RAW_INTR_STAT register.
	 *
	 * That is,
	 *   stat = dw_readl(IC_INTR_STAT);
	 * equals to,
	 *   stat = dw_readl(IC_RAW_INTR_STAT) & dw_readl(IC_INTR_MASK);
	 *
	 * The raw version might be useful for debugging purposes.
	 */
	stat = dw_readl(dev, DW_IC_INTR_STAT);

	/*
	 * Do not use the IC_CLR_INTR register to clear interrupts, or
	 * you'll miss some interrupts, triggered during the period from
	 * dw_readl(IC_INTR_STAT) to dw_readl(IC_CLR_INTR).
	 *
	 * Instead, use the separately-prepared IC_CLR_* registers.
	 */
	if (stat & DW_IC_INTR_RX_UNDER)
		dw_readl(dev, DW_IC_CLR_RX_UNDER);
	if (stat & DW_IC_INTR_RX_OVER)
		dw_readl(dev, DW_IC_CLR_RX_OVER);
	if (stat & DW_IC_INTR_TX_OVER)
		dw_readl(dev, DW_IC_CLR_TX_OVER);
	if (stat & DW_IC_INTR_RD_REQ)
		dw_readl(dev, DW_IC_CLR_RD_REQ);
	if (stat & DW_IC_INTR_TX_ABRT) {
		/*
		 * The IC_TX_ABRT_SOURCE register is cleared whenever
		 * the IC_CLR_TX_ABRT is read.  Preserve it beforehand.
		 */
		dev->abort_source = dw_readl(dev, DW_IC_TX_ABRT_SOURCE);
		dw_readl(dev, DW_IC_CLR_TX_ABRT);
	}
	if (stat & DW_IC_INTR_RX_DONE)
		dw_readl(dev, DW_IC_CLR_RX_DONE);
	if (stat & DW_IC_INTR_ACTIVITY)
		dw_readl(dev, DW_IC_CLR_ACTIVITY);
	if (stat & DW_IC_INTR_STOP_DET)
		dw_readl(dev, DW_IC_CLR_STOP_DET);
	if (stat & DW_IC_INTR_START_DET)
		dw_readl(dev, DW_IC_CLR_START_DET);
	if (stat & DW_IC_INTR_GEN_CALL)
		dw_readl(dev, DW_IC_CLR_GEN_CALL);

	return stat;
}