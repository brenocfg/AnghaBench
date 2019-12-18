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
typedef  scalar_t__ u_char ;
struct net_device {scalar_t__* dev_addr; int /*<<< orphan*/  irq; } ;
struct de4x5_private {scalar_t__ chipset; scalar_t__ bus_num; } ;
struct TYPE_2__ {scalar_t__ chipset; scalar_t__ bus; scalar_t__* addr; int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int ETH_ALEN ; 
 int /*<<< orphan*/  an_exception (struct de4x5_private*) ; 
 TYPE_1__ last ; 
 struct de4x5_private* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int
test_bad_enet(struct net_device *dev, int status)
{
    struct de4x5_private *lp = netdev_priv(dev);
    int i, tmp;

    for (tmp=0,i=0; i<ETH_ALEN; i++) tmp += (u_char)dev->dev_addr[i];
    if ((tmp == 0) || (tmp == 0x5fa)) {
	if ((lp->chipset == last.chipset) &&
	    (lp->bus_num == last.bus) && (lp->bus_num > 0)) {
	    for (i=0; i<ETH_ALEN; i++) dev->dev_addr[i] = last.addr[i];
	    for (i=ETH_ALEN-1; i>2; --i) {
		dev->dev_addr[i] += 1;
		if (dev->dev_addr[i] != 0) break;
	    }
	    for (i=0; i<ETH_ALEN; i++) last.addr[i] = dev->dev_addr[i];
	    if (!an_exception(lp)) {
		dev->irq = last.irq;
	    }

	    status = 0;
	}
    } else if (!status) {
	last.chipset = lp->chipset;
	last.bus = lp->bus_num;
	last.irq = dev->irq;
	for (i=0; i<ETH_ALEN; i++) last.addr[i] = dev->dev_addr[i];
    }

    return status;
}