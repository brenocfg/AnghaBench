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
struct net_device {unsigned int base_addr; scalar_t__ if_port; } ;
struct el3_private {int media_status; } ;

/* Variables and functions */
 int /*<<< orphan*/  EL3WINDOW (int) ; 
 unsigned int EL3_CMD ; 
 int MEDIA_LED ; 
 int MEDIA_TP ; 
 int StartCoax ; 
 int StopCoax ; 
 unsigned int WN4_MEDIA ; 
 struct el3_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  outw (int,unsigned int) ; 

__attribute__((used)) static void tc589_set_xcvr(struct net_device *dev, int if_port)
{
	struct el3_private *lp = netdev_priv(dev);
	unsigned int ioaddr = dev->base_addr;

	EL3WINDOW(0);
	switch (if_port) {
	case 0:
	case 1:
		outw(0, ioaddr + 6);
		break;
	case 2:
		outw(3<<14, ioaddr + 6);
		break;
	case 3:
		outw(1<<14, ioaddr + 6);
		break;
	}
	/* On PCMCIA, this just turns on the LED */
	outw((if_port == 2) ? StartCoax : StopCoax, ioaddr + EL3_CMD);
	/* 10baseT interface, enable link beat and jabber check. */
	EL3WINDOW(4);
	outw(MEDIA_LED | ((if_port < 2) ? MEDIA_TP : 0), ioaddr + WN4_MEDIA);
	EL3WINDOW(1);
	if (if_port == 2)
		lp->media_status = ((dev->if_port == 0) ? 0x8000 : 0x4000);
	else
		lp->media_status = ((dev->if_port == 0) ? 0x4010 : 0x8800);
}