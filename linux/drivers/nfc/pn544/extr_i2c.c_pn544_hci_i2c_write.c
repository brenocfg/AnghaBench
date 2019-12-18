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
struct sk_buff {int len; int /*<<< orphan*/  data; } ;
struct pn544_i2c_phy {scalar_t__ hard_fault; struct i2c_client* i2c_dev; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int EREMOTEIO ; 
 int /*<<< orphan*/  I2C_DUMP_SKB (char*,struct sk_buff*) ; 
 int i2c_master_send (struct i2c_client*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pn544_hci_i2c_add_len_crc (struct sk_buff*) ; 
 int /*<<< orphan*/  pn544_hci_i2c_remove_len_crc (struct sk_buff*) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int pn544_hci_i2c_write(void *phy_id, struct sk_buff *skb)
{
	int r;
	struct pn544_i2c_phy *phy = phy_id;
	struct i2c_client *client = phy->i2c_dev;

	if (phy->hard_fault != 0)
		return phy->hard_fault;

	usleep_range(3000, 6000);

	pn544_hci_i2c_add_len_crc(skb);

	I2C_DUMP_SKB("i2c frame written", skb);

	r = i2c_master_send(client, skb->data, skb->len);

	if (r == -EREMOTEIO) {	/* Retry, chip was in standby */
		usleep_range(6000, 10000);
		r = i2c_master_send(client, skb->data, skb->len);
	}

	if (r >= 0) {
		if (r != skb->len)
			r = -EREMOTEIO;
		else
			r = 0;
	}

	pn544_hci_i2c_remove_len_crc(skb);

	return r;
}