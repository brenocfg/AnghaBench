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
struct sk_buff {char* data; } ;
struct net_device {unsigned int base_addr; } ;
struct ei_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ AXNET_CMD ; 
 scalar_t__ AXNET_DATAPORT ; 
 int E8390_RREAD ; 
 int E8390_START ; 
 scalar_t__ EN0_RSARHI ; 
 scalar_t__ EN0_RSARLO ; 
 char inb (scalar_t__) ; 
 int /*<<< orphan*/  insw (scalar_t__,char*,int) ; 
 int /*<<< orphan*/  netdev_dbg (struct net_device*,char*,int) ; 
 struct ei_device* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_msg_rx_status (struct ei_device*) ; 
 int /*<<< orphan*/  outb_p (int,scalar_t__) ; 

__attribute__((used)) static void block_input(struct net_device *dev, int count,
			struct sk_buff *skb, int ring_offset)
{
    unsigned int nic_base = dev->base_addr;
    struct ei_device *ei_local = netdev_priv(dev);
    int xfer_count = count;
    char *buf = skb->data;

    if ((netif_msg_rx_status(ei_local)) && (count != 4))
	netdev_dbg(dev, "[bi=%d]\n", count+4);
    outb_p(ring_offset & 0xff, nic_base + EN0_RSARLO);
    outb_p(ring_offset >> 8, nic_base + EN0_RSARHI);
    outb_p(E8390_RREAD+E8390_START, nic_base + AXNET_CMD);

    insw(nic_base + AXNET_DATAPORT,buf,count>>1);
    if (count & 0x01)
	buf[count-1] = inb(nic_base + AXNET_DATAPORT), xfer_count++;

}