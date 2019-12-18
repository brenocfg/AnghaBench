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
struct iproc_adc_priv {int dummy; } ;
struct device {int dummy; } ;
struct iio_dev {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPROC_ANALOG_CONTROL ; 
 int /*<<< orphan*/  IPROC_AUX_DATA ; 
 int /*<<< orphan*/  IPROC_CONTROLLER_STATUS ; 
 int /*<<< orphan*/  IPROC_INTERRUPT_MASK ; 
 int /*<<< orphan*/  IPROC_INTERRUPT_STATUS ; 
 int /*<<< orphan*/  IPROC_INTERRUPT_THRES ; 
 int /*<<< orphan*/  IPROC_REGCTL1 ; 
 int /*<<< orphan*/  IPROC_REGCTL2 ; 
 int /*<<< orphan*/  IPROC_SOFT_BYPASS_CONTROL ; 
 int /*<<< orphan*/  IPROC_SOFT_BYPASS_DATA ; 
 struct iproc_adc_priv* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  iproc_adc_dbg_reg (struct device*,struct iproc_adc_priv*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void iproc_adc_reg_dump(struct iio_dev *indio_dev)
{
	struct device *dev = &indio_dev->dev;
	struct iproc_adc_priv *adc_priv = iio_priv(indio_dev);

	iproc_adc_dbg_reg(dev, adc_priv, IPROC_REGCTL1);
	iproc_adc_dbg_reg(dev, adc_priv, IPROC_REGCTL2);
	iproc_adc_dbg_reg(dev, adc_priv, IPROC_INTERRUPT_THRES);
	iproc_adc_dbg_reg(dev, adc_priv, IPROC_INTERRUPT_MASK);
	iproc_adc_dbg_reg(dev, adc_priv, IPROC_INTERRUPT_STATUS);
	iproc_adc_dbg_reg(dev, adc_priv, IPROC_CONTROLLER_STATUS);
	iproc_adc_dbg_reg(dev, adc_priv, IPROC_ANALOG_CONTROL);
	iproc_adc_dbg_reg(dev, adc_priv, IPROC_AUX_DATA);
	iproc_adc_dbg_reg(dev, adc_priv, IPROC_SOFT_BYPASS_CONTROL);
	iproc_adc_dbg_reg(dev, adc_priv, IPROC_SOFT_BYPASS_DATA);
}