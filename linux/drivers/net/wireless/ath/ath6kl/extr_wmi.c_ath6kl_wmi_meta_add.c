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
struct wmi_tx_meta_v2 {int dummy; } ;
struct wmi_tx_meta_v1 {int /*<<< orphan*/  rate_plcy_id; int /*<<< orphan*/  pkt_id; } ;
struct wmi {int dummy; } ;
struct sk_buff {scalar_t__ data; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  WMI_MAX_TX_META_SZ ; 
#define  WMI_META_VERSION_1 129 
#define  WMI_META_VERSION_2 128 
 int /*<<< orphan*/  memcpy (struct wmi_tx_meta_v2*,struct wmi_tx_meta_v2*,int) ; 
 int /*<<< orphan*/  skb_push (struct sk_buff*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ath6kl_wmi_meta_add(struct wmi *wmi, struct sk_buff *skb,
			       u8 *version, void *tx_meta_info)
{
	struct wmi_tx_meta_v1 *v1;
	struct wmi_tx_meta_v2 *v2;

	if (WARN_ON(skb == NULL || version == NULL))
		return -EINVAL;

	switch (*version) {
	case WMI_META_VERSION_1:
		skb_push(skb, WMI_MAX_TX_META_SZ);
		v1 = (struct wmi_tx_meta_v1 *) skb->data;
		v1->pkt_id = 0;
		v1->rate_plcy_id = 0;
		*version = WMI_META_VERSION_1;
		break;
	case WMI_META_VERSION_2:
		skb_push(skb, WMI_MAX_TX_META_SZ);
		v2 = (struct wmi_tx_meta_v2 *) skb->data;
		memcpy(v2, (struct wmi_tx_meta_v2 *) tx_meta_info,
		       sizeof(struct wmi_tx_meta_v2));
		break;
	}

	return 0;
}