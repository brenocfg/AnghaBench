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
typedef  int /*<<< orphan*/  tmp ;
struct sk_buff {scalar_t__ len; int /*<<< orphan*/  data; } ;
struct pn544_i2c_phy {struct i2c_client* i2c_dev; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EBADMSG ; 
 int ENOMEM ; 
 int EREMOTEIO ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  I2C_DUMP_SKB (char*,struct sk_buff*) ; 
 int PN544_HCI_I2C_LLC_MAX_SIZE ; 
 int PN544_HCI_I2C_LLC_MIN_SIZE ; 
 struct sk_buff* alloc_skb (int,int /*<<< orphan*/ ) ; 
 int check_crc (int /*<<< orphan*/ ,scalar_t__) ; 
 int i2c_master_recv (struct i2c_client*,int*,int) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  nfc_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int) ; 
 int* skb_put (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_put_u8 (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_trim (struct sk_buff*,scalar_t__) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int pn544_hci_i2c_read(struct pn544_i2c_phy *phy, struct sk_buff **skb)
{
	int r;
	u8 len;
	u8 tmp[PN544_HCI_I2C_LLC_MAX_SIZE - 1];
	struct i2c_client *client = phy->i2c_dev;

	r = i2c_master_recv(client, &len, 1);
	if (r != 1) {
		nfc_err(&client->dev, "cannot read len byte\n");
		return -EREMOTEIO;
	}

	if ((len < (PN544_HCI_I2C_LLC_MIN_SIZE - 1)) ||
	    (len > (PN544_HCI_I2C_LLC_MAX_SIZE - 1))) {
		nfc_err(&client->dev, "invalid len byte\n");
		r = -EBADMSG;
		goto flush;
	}

	*skb = alloc_skb(1 + len, GFP_KERNEL);
	if (*skb == NULL) {
		r = -ENOMEM;
		goto flush;
	}

	skb_put_u8(*skb, len);

	r = i2c_master_recv(client, skb_put(*skb, len), len);
	if (r != len) {
		kfree_skb(*skb);
		return -EREMOTEIO;
	}

	I2C_DUMP_SKB("i2c frame read", *skb);

	r = check_crc((*skb)->data, (*skb)->len);
	if (r != 0) {
		kfree_skb(*skb);
		r = -EBADMSG;
		goto flush;
	}

	skb_pull(*skb, 1);
	skb_trim(*skb, (*skb)->len - 2);

	usleep_range(3000, 6000);

	return 0;

flush:
	if (i2c_master_recv(client, tmp, sizeof(tmp)) < 0)
		r = -EREMOTEIO;

	usleep_range(3000, 6000);

	return r;
}