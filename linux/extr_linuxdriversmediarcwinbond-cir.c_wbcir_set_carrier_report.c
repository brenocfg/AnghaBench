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
struct wbcir_data {int carrier_report_enabled; int /*<<< orphan*/  spinlock; scalar_t__ sbase; TYPE_1__* dev; scalar_t__ ebase; scalar_t__ pulse_duration; } ;
struct rc_dev {struct wbcir_data* priv; } ;
struct TYPE_2__ {int /*<<< orphan*/  rx_resolution; scalar_t__ idle; } ;

/* Variables and functions */
 int /*<<< orphan*/  US_TO_NS (int) ; 
 int /*<<< orphan*/  WBCIR_BANK_2 ; 
 int /*<<< orphan*/  WBCIR_BANK_7 ; 
 int WBCIR_CNTR_EN ; 
 int WBCIR_CNTR_R ; 
 scalar_t__ WBCIR_REG_ECEIR_CCTL ; 
 scalar_t__ WBCIR_REG_SP3_BGDH ; 
 scalar_t__ WBCIR_REG_SP3_BGDL ; 
 scalar_t__ WBCIR_REG_SP3_RCCFG ; 
 int WBCIR_RX_T_OV ; 
 int /*<<< orphan*/  outb (int,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wbcir_select_bank (struct wbcir_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wbcir_set_bits (scalar_t__,int,int) ; 

__attribute__((used)) static int
wbcir_set_carrier_report(struct rc_dev *dev, int enable)
{
	struct wbcir_data *data = dev->priv;
	unsigned long flags;

	spin_lock_irqsave(&data->spinlock, flags);

	if (data->carrier_report_enabled == enable) {
		spin_unlock_irqrestore(&data->spinlock, flags);
		return 0;
	}

	data->pulse_duration = 0;
	wbcir_set_bits(data->ebase + WBCIR_REG_ECEIR_CCTL, WBCIR_CNTR_R,
						WBCIR_CNTR_EN | WBCIR_CNTR_R);

	if (enable && data->dev->idle)
		wbcir_set_bits(data->ebase + WBCIR_REG_ECEIR_CCTL,
				WBCIR_CNTR_EN, WBCIR_CNTR_EN | WBCIR_CNTR_R);

	/* Set a higher sampling resolution if carrier reports are enabled */
	wbcir_select_bank(data, WBCIR_BANK_2);
	data->dev->rx_resolution = US_TO_NS(enable ? 2 : 10);
	outb(enable ? 0x03 : 0x0f, data->sbase + WBCIR_REG_SP3_BGDL);
	outb(0x00, data->sbase + WBCIR_REG_SP3_BGDH);

	/* Enable oversampling if carrier reports are enabled */
	wbcir_select_bank(data, WBCIR_BANK_7);
	wbcir_set_bits(data->sbase + WBCIR_REG_SP3_RCCFG,
				enable ? WBCIR_RX_T_OV : 0, WBCIR_RX_T_OV);

	data->carrier_report_enabled = enable;
	spin_unlock_irqrestore(&data->spinlock, flags);

	return 0;
}