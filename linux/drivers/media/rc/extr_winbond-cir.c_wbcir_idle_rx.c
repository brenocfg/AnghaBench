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
struct wbcir_data {scalar_t__ rxstate; scalar_t__ sbase; scalar_t__ carrier_report_enabled; } ;
struct rc_dev {struct wbcir_data* priv; } ;

/* Variables and functions */
 scalar_t__ WBCIR_REG_SP3_ASCR ; 
 scalar_t__ WBCIR_RXSTATE_ACTIVE ; 
 scalar_t__ WBCIR_RXSTATE_INACTIVE ; 
 int /*<<< orphan*/  WBCIR_RX_DISABLE ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  wbcir_carrier_report (struct wbcir_data*) ; 

__attribute__((used)) static void
wbcir_idle_rx(struct rc_dev *dev, bool idle)
{
	struct wbcir_data *data = dev->priv;

	if (!idle && data->rxstate == WBCIR_RXSTATE_INACTIVE)
		data->rxstate = WBCIR_RXSTATE_ACTIVE;

	if (idle && data->rxstate != WBCIR_RXSTATE_INACTIVE) {
		data->rxstate = WBCIR_RXSTATE_INACTIVE;

		if (data->carrier_report_enabled)
			wbcir_carrier_report(data);

		/* Tell hardware to go idle by setting RXINACTIVE */
		outb(WBCIR_RX_DISABLE, data->sbase + WBCIR_REG_SP3_ASCR);
	}
}