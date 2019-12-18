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
typedef  int u8 ;
struct st_nci_i2c_phy {struct i2c_client* i2c_dev; } ;
struct sk_buff {scalar_t__ data; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int EBADMSG ; 
 int ENOMEM ; 
 int EREMOTEIO ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int ST_NCI_I2C_MAX_SIZE ; 
 int ST_NCI_I2C_MIN_SIZE ; 
 struct sk_buff* alloc_skb (int,int /*<<< orphan*/ ) ; 
 int be16_to_cpu (int /*<<< orphan*/ ) ; 
 int i2c_master_recv (struct i2c_client*,int*,int) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,int*,int) ; 
 int /*<<< orphan*/  nfc_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int st_nci_i2c_read(struct st_nci_i2c_phy *phy,
				 struct sk_buff **skb)
{
	int r;
	u8 len;
	u8 buf[ST_NCI_I2C_MAX_SIZE];
	struct i2c_client *client = phy->i2c_dev;

	r = i2c_master_recv(client, buf, ST_NCI_I2C_MIN_SIZE);
	if (r < 0) {  /* Retry, chip was in standby */
		usleep_range(1000, 4000);
		r = i2c_master_recv(client, buf, ST_NCI_I2C_MIN_SIZE);
	}

	if (r != ST_NCI_I2C_MIN_SIZE)
		return -EREMOTEIO;

	len = be16_to_cpu(*(__be16 *) (buf + 2));
	if (len > ST_NCI_I2C_MAX_SIZE) {
		nfc_err(&client->dev, "invalid frame len\n");
		return -EBADMSG;
	}

	*skb = alloc_skb(ST_NCI_I2C_MIN_SIZE + len, GFP_KERNEL);
	if (*skb == NULL)
		return -ENOMEM;

	skb_reserve(*skb, ST_NCI_I2C_MIN_SIZE);
	skb_put(*skb, ST_NCI_I2C_MIN_SIZE);
	memcpy((*skb)->data, buf, ST_NCI_I2C_MIN_SIZE);

	if (!len)
		return 0;

	r = i2c_master_recv(client, buf, len);
	if (r != len) {
		kfree_skb(*skb);
		return -EREMOTEIO;
	}

	skb_put(*skb, len);
	memcpy((*skb)->data + ST_NCI_I2C_MIN_SIZE, buf, len);

	return 0;
}