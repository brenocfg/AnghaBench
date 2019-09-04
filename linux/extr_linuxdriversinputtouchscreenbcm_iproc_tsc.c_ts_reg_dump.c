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
struct iproc_ts_priv {TYPE_1__* pdev; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ANALOG_CONTROL ; 
 int /*<<< orphan*/  AUX_DATA ; 
 int /*<<< orphan*/  CONTROLLER_STATUS ; 
 int /*<<< orphan*/  DEBOUNCE_CNTR_STAT ; 
 int /*<<< orphan*/  FIFO_DATA ; 
 int /*<<< orphan*/  INTERRUPT_MASK ; 
 int /*<<< orphan*/  INTERRUPT_STATUS ; 
 int /*<<< orphan*/  INTERRUPT_THRES ; 
 int /*<<< orphan*/  REGCTL1 ; 
 int /*<<< orphan*/  REGCTL2 ; 
 int /*<<< orphan*/  REM_CNTR_STAT ; 
 int /*<<< orphan*/  SCAN_CNTR_STAT ; 
 int /*<<< orphan*/  SETTLING_TIMER_STAT ; 
 int /*<<< orphan*/  SOFT_BYPASS_CONTROL ; 
 int /*<<< orphan*/  SOFT_BYPASS_DATA ; 
 int /*<<< orphan*/  SPARE_REG ; 
 int /*<<< orphan*/  dbg_reg (struct device*,struct iproc_ts_priv*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ts_reg_dump(struct iproc_ts_priv *priv)
{
	struct device *dev = &priv->pdev->dev;

	dbg_reg(dev, priv, REGCTL1);
	dbg_reg(dev, priv, REGCTL2);
	dbg_reg(dev, priv, INTERRUPT_THRES);
	dbg_reg(dev, priv, INTERRUPT_MASK);
	dbg_reg(dev, priv, INTERRUPT_STATUS);
	dbg_reg(dev, priv, CONTROLLER_STATUS);
	dbg_reg(dev, priv, FIFO_DATA);
	dbg_reg(dev, priv, ANALOG_CONTROL);
	dbg_reg(dev, priv, AUX_DATA);
	dbg_reg(dev, priv, DEBOUNCE_CNTR_STAT);
	dbg_reg(dev, priv, SCAN_CNTR_STAT);
	dbg_reg(dev, priv, REM_CNTR_STAT);
	dbg_reg(dev, priv, SETTLING_TIMER_STAT);
	dbg_reg(dev, priv, SPARE_REG);
	dbg_reg(dev, priv, SOFT_BYPASS_CONTROL);
	dbg_reg(dev, priv, SOFT_BYPASS_DATA);
}