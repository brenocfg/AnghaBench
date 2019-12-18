#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
typedef  int u32 ;
struct ptp_qoriq_registers {TYPE_2__* ctrl_regs; TYPE_1__* alarm_regs; } ;
struct ptp_qoriq {int (* read ) (int /*<<< orphan*/ *) ;int alarm_value; int alarm_interval; int /*<<< orphan*/  (* write ) (int /*<<< orphan*/ *,int) ;int /*<<< orphan*/  clock; int /*<<< orphan*/  lock; struct ptp_qoriq_registers regs; } ;
struct ptp_clock_event {int timestamp; int /*<<< orphan*/  type; scalar_t__ index; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_4__ {int /*<<< orphan*/  tmr_tevent; int /*<<< orphan*/  tmr_temask; } ;
struct TYPE_3__ {int /*<<< orphan*/  tmr_alarm2_h; int /*<<< orphan*/  tmr_alarm2_l; } ;

/* Variables and functions */
 int ALM2 ; 
 int ALM2EN ; 
 int ETS1 ; 
 int ETS2 ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int PP1 ; 
 int /*<<< orphan*/  PTP_CLOCK_ALARM ; 
 int /*<<< orphan*/  PTP_CLOCK_PPS ; 
 int /*<<< orphan*/  extts_clean_up (struct ptp_qoriq*,int,int) ; 
 int /*<<< orphan*/  ptp_clock_event (int /*<<< orphan*/ ,struct ptp_clock_event*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int stub1 (int /*<<< orphan*/ *) ; 
 int stub2 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ *,int) ; 
 int stub5 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub6 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stub7 (int /*<<< orphan*/ *,int) ; 

irqreturn_t ptp_qoriq_isr(int irq, void *priv)
{
	struct ptp_qoriq *ptp_qoriq = priv;
	struct ptp_qoriq_registers *regs = &ptp_qoriq->regs;
	struct ptp_clock_event event;
	u64 ns;
	u32 ack = 0, lo, hi, mask, val, irqs;

	spin_lock(&ptp_qoriq->lock);

	val = ptp_qoriq->read(&regs->ctrl_regs->tmr_tevent);
	mask = ptp_qoriq->read(&regs->ctrl_regs->tmr_temask);

	spin_unlock(&ptp_qoriq->lock);

	irqs = val & mask;

	if (irqs & ETS1) {
		ack |= ETS1;
		extts_clean_up(ptp_qoriq, 0, true);
	}

	if (irqs & ETS2) {
		ack |= ETS2;
		extts_clean_up(ptp_qoriq, 1, true);
	}

	if (irqs & ALM2) {
		ack |= ALM2;
		if (ptp_qoriq->alarm_value) {
			event.type = PTP_CLOCK_ALARM;
			event.index = 0;
			event.timestamp = ptp_qoriq->alarm_value;
			ptp_clock_event(ptp_qoriq->clock, &event);
		}
		if (ptp_qoriq->alarm_interval) {
			ns = ptp_qoriq->alarm_value + ptp_qoriq->alarm_interval;
			hi = ns >> 32;
			lo = ns & 0xffffffff;
			ptp_qoriq->write(&regs->alarm_regs->tmr_alarm2_l, lo);
			ptp_qoriq->write(&regs->alarm_regs->tmr_alarm2_h, hi);
			ptp_qoriq->alarm_value = ns;
		} else {
			spin_lock(&ptp_qoriq->lock);
			mask = ptp_qoriq->read(&regs->ctrl_regs->tmr_temask);
			mask &= ~ALM2EN;
			ptp_qoriq->write(&regs->ctrl_regs->tmr_temask, mask);
			spin_unlock(&ptp_qoriq->lock);
			ptp_qoriq->alarm_value = 0;
			ptp_qoriq->alarm_interval = 0;
		}
	}

	if (irqs & PP1) {
		ack |= PP1;
		event.type = PTP_CLOCK_PPS;
		ptp_clock_event(ptp_qoriq->clock, &event);
	}

	if (ack) {
		ptp_qoriq->write(&regs->ctrl_regs->tmr_tevent, ack);
		return IRQ_HANDLED;
	} else
		return IRQ_NONE;
}