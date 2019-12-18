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
struct wmi {int dummy; } ;
struct sk_buff {int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  NO_SYNC_WMIFLAG ; 
 int /*<<< orphan*/  WMI_TEST_CMDID ; 
 int ath6kl_wmi_cmd_send (struct wmi*,int /*<<< orphan*/ ,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sk_buff* ath6kl_wmi_get_new_buf (size_t) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void*,size_t) ; 

int ath6kl_wmi_test_cmd(struct wmi *wmi, void *buf, size_t len)
{
	struct sk_buff *skb;
	int ret;

	skb = ath6kl_wmi_get_new_buf(len);
	if (!skb)
		return -ENOMEM;

	memcpy(skb->data, buf, len);

	ret = ath6kl_wmi_cmd_send(wmi, 0, skb, WMI_TEST_CMDID, NO_SYNC_WMIFLAG);

	return ret;
}