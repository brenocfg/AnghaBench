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
struct x25_asy {unsigned char* xbuff; int xleft; unsigned char* xhead; unsigned char* rbuff; int rcount; int buffsize; int /*<<< orphan*/  lock; int /*<<< orphan*/  flags; } ;
struct TYPE_2__ {int /*<<< orphan*/  rx_over_errors; int /*<<< orphan*/  tx_dropped; } ;
struct net_device {int mtu; TYPE_1__ stats; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  SLF_ERROR ; 
 int /*<<< orphan*/  kfree (unsigned char*) ; 
 unsigned char* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char*,int) ; 
 struct x25_asy* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 unsigned char* xchg (unsigned char**,unsigned char*) ; 

__attribute__((used)) static int x25_asy_change_mtu(struct net_device *dev, int newmtu)
{
	struct x25_asy *sl = netdev_priv(dev);
	unsigned char *xbuff, *rbuff;
	int len;

	len = 2 * newmtu;
	xbuff = kmalloc(len + 4, GFP_ATOMIC);
	rbuff = kmalloc(len + 4, GFP_ATOMIC);

	if (xbuff == NULL || rbuff == NULL) {
		kfree(xbuff);
		kfree(rbuff);
		return -ENOMEM;
	}

	spin_lock_bh(&sl->lock);
	xbuff    = xchg(&sl->xbuff, xbuff);
	if (sl->xleft)  {
		if (sl->xleft <= len)  {
			memcpy(sl->xbuff, sl->xhead, sl->xleft);
		} else  {
			sl->xleft = 0;
			dev->stats.tx_dropped++;
		}
	}
	sl->xhead = sl->xbuff;

	rbuff	 = xchg(&sl->rbuff, rbuff);
	if (sl->rcount)  {
		if (sl->rcount <= len) {
			memcpy(sl->rbuff, rbuff, sl->rcount);
		} else  {
			sl->rcount = 0;
			dev->stats.rx_over_errors++;
			set_bit(SLF_ERROR, &sl->flags);
		}
	}

	dev->mtu    = newmtu;
	sl->buffsize = len;

	spin_unlock_bh(&sl->lock);

	kfree(xbuff);
	kfree(rbuff);
	return 0;
}