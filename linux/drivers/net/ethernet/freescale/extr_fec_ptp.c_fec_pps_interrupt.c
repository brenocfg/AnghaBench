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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct ptp_clock_event {int /*<<< orphan*/  type; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {int mask; } ;
struct fec_enet_private {int next_counter; int reload_period; int /*<<< orphan*/  ptp_clock; TYPE_1__ cc; scalar_t__ hwp; int /*<<< orphan*/  pps_channel; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 scalar_t__ FEC_TCCR (int /*<<< orphan*/ ) ; 
 scalar_t__ FEC_TCSR (int /*<<< orphan*/ ) ; 
 int FEC_T_TF_MASK ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  PTP_CLOCK_PPS ; 
 struct fec_enet_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  ptp_clock_event (int /*<<< orphan*/ ,struct ptp_clock_event*) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static irqreturn_t fec_pps_interrupt(int irq, void *dev_id)
{
	struct net_device *ndev = dev_id;
	struct fec_enet_private *fep = netdev_priv(ndev);
	u32 val;
	u8 channel = fep->pps_channel;
	struct ptp_clock_event event;

	val = readl(fep->hwp + FEC_TCSR(channel));
	if (val & FEC_T_TF_MASK) {
		/* Write the next next compare(not the next according the spec)
		 * value to the register
		 */
		writel(fep->next_counter, fep->hwp + FEC_TCCR(channel));
		do {
			writel(val, fep->hwp + FEC_TCSR(channel));
		} while (readl(fep->hwp + FEC_TCSR(channel)) & FEC_T_TF_MASK);

		/* Update the counter; */
		fep->next_counter = (fep->next_counter + fep->reload_period) &
				fep->cc.mask;

		event.type = PTP_CLOCK_PPS;
		ptp_clock_event(fep->ptp_clock, &event);
		return IRQ_HANDLED;
	}

	return IRQ_NONE;
}