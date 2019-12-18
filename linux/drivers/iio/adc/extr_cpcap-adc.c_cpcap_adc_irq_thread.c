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
struct iio_dev {int dummy; } ;
struct cpcap_adc {int done; int /*<<< orphan*/  wq_data_avail; int /*<<< orphan*/  reg; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  CPCAP_BIT_ADTRIG_DIS ; 
 int /*<<< orphan*/  CPCAP_REG_ADCC2 ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 struct cpcap_adc* iio_priv (struct iio_dev*) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t cpcap_adc_irq_thread(int irq, void *data)
{
	struct iio_dev *indio_dev = data;
	struct cpcap_adc *ddata = iio_priv(indio_dev);
	int error;

	error = regmap_update_bits(ddata->reg, CPCAP_REG_ADCC2,
				   CPCAP_BIT_ADTRIG_DIS,
				   CPCAP_BIT_ADTRIG_DIS);
	if (error)
		return IRQ_NONE;

	ddata->done = true;
	wake_up_interruptible(&ddata->wq_data_avail);

	return IRQ_HANDLED;
}