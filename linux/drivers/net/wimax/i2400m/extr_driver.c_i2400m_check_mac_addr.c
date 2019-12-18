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
struct sk_buff {scalar_t__ data; } ;
struct net_device {int addr_len; int /*<<< orphan*/  dev_addr; int /*<<< orphan*/  perm_addr; } ;
struct i2400m_tlv_detailed_device_info {int /*<<< orphan*/  mac_address; } ;
struct TYPE_2__ {struct net_device* net_dev; } ;
struct i2400m {TYPE_1__ wimax_dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int ETH_ALEN ; 
 scalar_t__ IS_ERR (struct sk_buff*) ; 
 int PTR_ERR (struct sk_buff*) ; 
 int /*<<< orphan*/  d_fnend (int,struct device*,char*,struct i2400m*,int) ; 
 int /*<<< orphan*/  d_fnstart (int,struct device*,char*,struct i2400m*) ; 
 int /*<<< orphan*/  d_printf (int,struct device*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*,...) ; 
 struct device* i2400m_dev (struct i2400m*) ; 
 struct sk_buff* i2400m_get_device_info (struct i2400m*) ; 
 scalar_t__ is_zero_ether_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static
int i2400m_check_mac_addr(struct i2400m *i2400m)
{
	int result;
	struct device *dev = i2400m_dev(i2400m);
	struct sk_buff *skb;
	const struct i2400m_tlv_detailed_device_info *ddi;
	struct net_device *net_dev = i2400m->wimax_dev.net_dev;

	d_fnstart(3, dev, "(i2400m %p)\n", i2400m);
	skb = i2400m_get_device_info(i2400m);
	if (IS_ERR(skb)) {
		result = PTR_ERR(skb);
		dev_err(dev, "Cannot verify MAC address, error reading: %d\n",
			result);
		goto error;
	}
	/* Extract MAC address */
	ddi = (void *) skb->data;
	BUILD_BUG_ON(ETH_ALEN != sizeof(ddi->mac_address));
	d_printf(2, dev, "GET DEVICE INFO: mac addr %pM\n",
		 ddi->mac_address);
	if (!memcmp(net_dev->perm_addr, ddi->mac_address,
		   sizeof(ddi->mac_address)))
		goto ok;
	dev_warn(dev, "warning: device reports a different MAC address "
		 "to that of boot mode's\n");
	dev_warn(dev, "device reports     %pM\n", ddi->mac_address);
	dev_warn(dev, "boot mode reported %pM\n", net_dev->perm_addr);
	if (is_zero_ether_addr(ddi->mac_address))
		dev_err(dev, "device reports an invalid MAC address, "
			"not updating\n");
	else {
		dev_warn(dev, "updating MAC address\n");
		net_dev->addr_len = ETH_ALEN;
		memcpy(net_dev->perm_addr, ddi->mac_address, ETH_ALEN);
		memcpy(net_dev->dev_addr, ddi->mac_address, ETH_ALEN);
	}
ok:
	result = 0;
	kfree_skb(skb);
error:
	d_fnend(3, dev, "(i2400m %p) = %d\n", i2400m, result);
	return result;
}