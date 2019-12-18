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
typedef  size_t u8 ;
struct sk_buff {int* data; } ;
struct port100_in_rf_setting {int dummy; } ;
struct port100 {int dummy; } ;
struct nfc_digital_dev {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 scalar_t__ IS_ERR (struct sk_buff*) ; 
 size_t NFC_DIGITAL_RF_TECH_LAST ; 
 int /*<<< orphan*/  PORT100_CMD_IN_SET_RF ; 
 int PTR_ERR (struct sk_buff*) ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/ * in_rf_settings ; 
 struct port100* nfc_digital_get_drvdata (struct nfc_digital_dev*) ; 
 struct sk_buff* port100_alloc_skb (struct port100*,int) ; 
 struct sk_buff* port100_send_cmd_sync (struct port100*,int /*<<< orphan*/ ,struct sk_buff*) ; 
 int /*<<< orphan*/  skb_put_data (struct sk_buff*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int port100_in_set_rf(struct nfc_digital_dev *ddev, u8 rf)
{
	struct port100 *dev = nfc_digital_get_drvdata(ddev);
	struct sk_buff *skb;
	struct sk_buff *resp;
	int rc;

	if (rf >= NFC_DIGITAL_RF_TECH_LAST)
		return -EINVAL;

	skb = port100_alloc_skb(dev, sizeof(struct port100_in_rf_setting));
	if (!skb)
		return -ENOMEM;

	skb_put_data(skb, &in_rf_settings[rf],
		     sizeof(struct port100_in_rf_setting));

	resp = port100_send_cmd_sync(dev, PORT100_CMD_IN_SET_RF, skb);

	if (IS_ERR(resp))
		return PTR_ERR(resp);

	rc = resp->data[0];

	dev_kfree_skb(resp);

	return rc;
}