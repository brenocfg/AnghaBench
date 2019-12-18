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
struct ath10k {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH10K_DBG_WMI ; 
 int EPROTO ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 scalar_t__ IS_ERR (void const**) ; 
 int PTR_ERR (void const**) ; 
 size_t WMI_TLV_TAG_ARRAY_BYTE ; 
 int /*<<< orphan*/  ath10k_dbg (struct ath10k*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  ath10k_warn (struct ath10k*,char*,int) ; 
 int ath10k_wmi_tlv_len (void const*) ; 
 void** ath10k_wmi_tlv_parse_alloc (struct ath10k*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (void const**) ; 
 int /*<<< orphan*/  trace_ath10k_wmi_diag (struct ath10k*,void const*,int) ; 

__attribute__((used)) static int ath10k_wmi_tlv_event_diag(struct ath10k *ar,
				     struct sk_buff *skb)
{
	const void **tb;
	const void *data;
	int ret, len;

	tb = ath10k_wmi_tlv_parse_alloc(ar, skb->data, skb->len, GFP_ATOMIC);
	if (IS_ERR(tb)) {
		ret = PTR_ERR(tb);
		ath10k_warn(ar, "failed to parse tlv: %d\n", ret);
		return ret;
	}

	data = tb[WMI_TLV_TAG_ARRAY_BYTE];
	if (!data) {
		kfree(tb);
		return -EPROTO;
	}
	len = ath10k_wmi_tlv_len(data);

	ath10k_dbg(ar, ATH10K_DBG_WMI, "wmi tlv diag event len %d\n", len);
	trace_ath10k_wmi_diag(ar, data, len);

	kfree(tb);
	return 0;
}