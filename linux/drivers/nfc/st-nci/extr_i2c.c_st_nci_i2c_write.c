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
struct st_nci_i2c_phy {TYPE_1__* ndlc; struct i2c_client* i2c_dev; } ;
struct sk_buff {int len; int /*<<< orphan*/  data; } ;
struct i2c_client {int dummy; } ;
struct TYPE_2__ {scalar_t__ hard_fault; } ;

/* Variables and functions */
 int EREMOTEIO ; 
 int i2c_master_send (struct i2c_client*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int st_nci_i2c_write(void *phy_id, struct sk_buff *skb)
{
	int r;
	struct st_nci_i2c_phy *phy = phy_id;
	struct i2c_client *client = phy->i2c_dev;

	if (phy->ndlc->hard_fault != 0)
		return phy->ndlc->hard_fault;

	r = i2c_master_send(client, skb->data, skb->len);
	if (r < 0) {  /* Retry, chip was in standby */
		usleep_range(1000, 4000);
		r = i2c_master_send(client, skb->data, skb->len);
	}

	if (r >= 0) {
		if (r != skb->len)
			r = -EREMOTEIO;
		else
			r = 0;
	}

	return r;
}