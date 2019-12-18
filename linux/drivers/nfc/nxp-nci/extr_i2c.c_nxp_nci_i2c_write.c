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
struct nxp_nci_i2c_phy {scalar_t__ hard_fault; struct i2c_client* i2c_dev; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EREMOTEIO ; 
 int i2c_master_send (struct i2c_client*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  nfc_err (int /*<<< orphan*/ *,char*,int,...) ; 

__attribute__((used)) static int nxp_nci_i2c_write(void *phy_id, struct sk_buff *skb)
{
	int r;
	struct nxp_nci_i2c_phy *phy = phy_id;
	struct i2c_client *client = phy->i2c_dev;

	if (phy->hard_fault != 0)
		return phy->hard_fault;

	r = i2c_master_send(client, skb->data, skb->len);
	if (r < 0) {
		/* Retry, chip was in standby */
		msleep(110);
		r = i2c_master_send(client, skb->data, skb->len);
	}

	if (r < 0) {
		nfc_err(&client->dev, "Error %d on I2C send\n", r);
	} else if (r != skb->len) {
		nfc_err(&client->dev,
			"Invalid length sent: %u (expected %u)\n",
			r, skb->len);
		r = -EREMOTEIO;
	} else {
		/* Success but return 0 and not number of bytes */
		r = 0;
	}

	return r;
}