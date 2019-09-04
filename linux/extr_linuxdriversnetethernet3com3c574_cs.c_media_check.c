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
struct timer_list {int dummy; } ;
struct net_device {unsigned int base_addr; int mtu; int /*<<< orphan*/  irq; } ;
struct TYPE_4__ {void* expires; } ;
struct el3_private {int fast_poll; unsigned short media_status; unsigned short partner; unsigned short advertising; TYPE_2__ media; int /*<<< orphan*/  window_lock; int /*<<< orphan*/  phys; TYPE_1__* p_dev; } ;
struct TYPE_3__ {struct net_device* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  EL3WINDOW (int) ; 
 scalar_t__ EL3_STATUS ; 
 int HZ ; 
 int IntLatch ; 
 scalar_t__ Timer ; 
 scalar_t__ Wn3_MAC_Ctrl ; 
 int /*<<< orphan*/  add_timer (TYPE_2__*) ; 
 int /*<<< orphan*/  el3_interrupt (int /*<<< orphan*/ ,struct net_device*) ; 
 struct el3_private* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int inb (scalar_t__) ; 
 int inw (scalar_t__) ; 
 void* jiffies ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 struct el3_private* lp ; 
 unsigned short mdio_read (unsigned int,int /*<<< orphan*/ ,int) ; 
 unsigned short media ; 
 int /*<<< orphan*/  netdev_info (struct net_device*,char*,...) ; 
 int /*<<< orphan*/  netif_device_present (struct net_device*) ; 
 int /*<<< orphan*/  outb (int,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void media_check(struct timer_list *t)
{
	struct el3_private *lp = from_timer(lp, t, media);
	struct net_device *dev = lp->p_dev->priv;
	unsigned int ioaddr = dev->base_addr;
	unsigned long flags;
	unsigned short /* cable, */ media, partner;

	if (!netif_device_present(dev))
		goto reschedule;
	
	/* Check for pending interrupt with expired latency timer: with
	   this, we can limp along even if the interrupt is blocked */
	if ((inw(ioaddr + EL3_STATUS) & IntLatch) && (inb(ioaddr + Timer) == 0xff)) {
		if (!lp->fast_poll)
			netdev_info(dev, "interrupt(s) dropped!\n");

		local_irq_save(flags);
		el3_interrupt(dev->irq, dev);
		local_irq_restore(flags);

		lp->fast_poll = HZ;
	}
	if (lp->fast_poll) {
		lp->fast_poll--;
		lp->media.expires = jiffies + 2*HZ/100;
		add_timer(&lp->media);
		return;
	}

	spin_lock_irqsave(&lp->window_lock, flags);
	EL3WINDOW(4);
	media = mdio_read(ioaddr, lp->phys, 1);
	partner = mdio_read(ioaddr, lp->phys, 5);
	EL3WINDOW(1);
	
	if (media != lp->media_status) {
		if ((media ^ lp->media_status) & 0x0004)
			netdev_info(dev, "%s link beat\n",
				    (lp->media_status & 0x0004) ? "lost" : "found");
		if ((media ^ lp->media_status) & 0x0020) {
			lp->partner = 0;
			if (lp->media_status & 0x0020) {
				netdev_info(dev, "autonegotiation restarted\n");
			} else if (partner) {
				partner &= lp->advertising;
				lp->partner = partner;
				netdev_info(dev, "autonegotiation complete: "
					    "%dbaseT-%cD selected\n",
					    (partner & 0x0180) ? 100 : 10,
					    (partner & 0x0140) ? 'F' : 'H');
			} else {
				netdev_info(dev, "link partner did not autonegotiate\n");
			}

			EL3WINDOW(3);
			outb((partner & 0x0140 ? 0x20 : 0) |
				 (dev->mtu > 1500 ? 0x40 : 0), ioaddr + Wn3_MAC_Ctrl);
			EL3WINDOW(1);

		}
		if (media & 0x0010)
			netdev_info(dev, "remote fault detected\n");
		if (media & 0x0002)
			netdev_info(dev, "jabber detected\n");
		lp->media_status = media;
	}
	spin_unlock_irqrestore(&lp->window_lock, flags);

reschedule:
	lp->media.expires = jiffies + HZ;
	add_timer(&lp->media);
}