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
typedef  int u32 ;
struct TYPE_2__ {int /*<<< orphan*/  flags; } ;
struct rtl8169_private {int irq_mask; scalar_t__ mac_version; int /*<<< orphan*/  napi; TYPE_1__ wk; int /*<<< orphan*/  dev; int /*<<< orphan*/  phydev; int /*<<< orphan*/  irq_enabled; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int LinkChg ; 
 int /*<<< orphan*/  RTL_FLAG_TASK_RESET_PENDING ; 
 scalar_t__ RTL_GIGA_MAC_VER_11 ; 
 int RxFIFOOver ; 
 int SYSErr ; 
 int /*<<< orphan*/  napi_schedule_irqoff (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netif_stop_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phy_mac_interrupt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl8169_pcierr_interrupt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl_ack_events (struct rtl8169_private*,int) ; 
 int rtl_get_events (struct rtl8169_private*) ; 
 int /*<<< orphan*/  rtl_irq_disable (struct rtl8169_private*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static irqreturn_t rtl8169_interrupt(int irq, void *dev_instance)
{
	struct rtl8169_private *tp = dev_instance;
	u32 status = rtl_get_events(tp);

	if (!tp->irq_enabled || (status & 0xffff) == 0xffff ||
	    !(status & tp->irq_mask))
		return IRQ_NONE;

	if (unlikely(status & SYSErr)) {
		rtl8169_pcierr_interrupt(tp->dev);
		goto out;
	}

	if (status & LinkChg)
		phy_mac_interrupt(tp->phydev);

	if (unlikely(status & RxFIFOOver &&
	    tp->mac_version == RTL_GIGA_MAC_VER_11)) {
		netif_stop_queue(tp->dev);
		/* XXX - Hack alert. See rtl_task(). */
		set_bit(RTL_FLAG_TASK_RESET_PENDING, tp->wk.flags);
	}

	rtl_irq_disable(tp);
	napi_schedule_irqoff(&tp->napi);
out:
	rtl_ack_events(tp, status);

	return IRQ_HANDLED;
}