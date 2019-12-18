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
typedef  int /*<<< orphan*/  uint16_t ;
struct adis {TYPE_1__* data; } ;
struct TYPE_2__ {int (* enable_irq ) (struct adis*,int) ;int /*<<< orphan*/  msc_ctrl_reg; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADIS_MSC_CTRL_DATA_RDY_DIO2 ; 
 int /*<<< orphan*/  ADIS_MSC_CTRL_DATA_RDY_EN ; 
 int /*<<< orphan*/  ADIS_MSC_CTRL_DATA_RDY_POL_HIGH ; 
 int adis_read_reg_16 (struct adis*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int adis_write_reg_16 (struct adis*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub1 (struct adis*,int) ; 

int adis_enable_irq(struct adis *adis, bool enable)
{
	int ret = 0;
	uint16_t msc;

	if (adis->data->enable_irq)
		return adis->data->enable_irq(adis, enable);

	ret = adis_read_reg_16(adis, adis->data->msc_ctrl_reg, &msc);
	if (ret)
		goto error_ret;

	msc |= ADIS_MSC_CTRL_DATA_RDY_POL_HIGH;
	msc &= ~ADIS_MSC_CTRL_DATA_RDY_DIO2;
	if (enable)
		msc |= ADIS_MSC_CTRL_DATA_RDY_EN;
	else
		msc &= ~ADIS_MSC_CTRL_DATA_RDY_EN;

	ret = adis_write_reg_16(adis, adis->data->msc_ctrl_reg, msc);

error_ret:
	return ret;
}