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
struct sk_buff {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
struct net_device {int dummy; } ;
struct i2400m {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  I2400M_PT_DATA ; 
 int /*<<< orphan*/  d_dump (int,struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  d_fnend (int,struct device*,char*,struct i2400m*,struct net_device*,struct sk_buff*,int) ; 
 int /*<<< orphan*/  d_fnstart (int,struct device*,char*,struct i2400m*,struct net_device*,struct sk_buff*) ; 
 int /*<<< orphan*/  d_printf (int,struct device*,char*,struct sk_buff*,int /*<<< orphan*/ ) ; 
 struct device* i2400m_dev (struct i2400m*) ; 
 int i2400m_tx (struct i2400m*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2400m_tx_prep_header (struct sk_buff*) ; 
 int /*<<< orphan*/  netif_trans_update (struct net_device*) ; 

__attribute__((used)) static
int i2400m_net_tx(struct i2400m *i2400m, struct net_device *net_dev,
		  struct sk_buff *skb)
{
	int result;
	struct device *dev = i2400m_dev(i2400m);

	d_fnstart(3, dev, "(i2400m %p net_dev %p skb %p)\n",
		  i2400m, net_dev, skb);
	/* FIXME: check eth hdr, only IPv4 is routed by the device as of now */
	netif_trans_update(net_dev);
	i2400m_tx_prep_header(skb);
	d_printf(3, dev, "NETTX: skb %p sending %d bytes to radio\n",
		 skb, skb->len);
	d_dump(4, dev, skb->data, skb->len);
	result = i2400m_tx(i2400m, skb->data, skb->len, I2400M_PT_DATA);
	d_fnend(3, dev, "(i2400m %p net_dev %p skb %p) = %d\n",
		i2400m, net_dev, skb, result);
	return result;
}