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
struct dw_hdmi_cec {int tx_done; int rx_done; int /*<<< orphan*/  rx_msg; int /*<<< orphan*/  tx_status; } ;
struct cec_adapter {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 struct dw_hdmi_cec* cec_get_drvdata (struct cec_adapter*) ; 
 int /*<<< orphan*/  cec_received_msg (struct cec_adapter*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cec_transmit_attempt_done (struct cec_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_rmb () ; 

__attribute__((used)) static irqreturn_t dw_hdmi_cec_thread(int irq, void *data)
{
	struct cec_adapter *adap = data;
	struct dw_hdmi_cec *cec = cec_get_drvdata(adap);

	if (cec->tx_done) {
		cec->tx_done = false;
		cec_transmit_attempt_done(adap, cec->tx_status);
	}
	if (cec->rx_done) {
		cec->rx_done = false;
		smp_rmb();
		cec_received_msg(adap, &cec->rx_msg);
	}
	return IRQ_HANDLED;
}