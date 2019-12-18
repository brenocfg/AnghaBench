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
typedef  int u16 ;
struct sk_buff {scalar_t__ data; } ;
struct qtnf_wmac {struct qtnf_vif* iflist; } ;
struct qtnf_vif {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  len; } ;
struct qlink_event {size_t vifid; TYPE_1__ mhdr; int /*<<< orphan*/  event_id; } ;

/* Variables and functions */
 int EINVAL ; 
#define  QLINK_EVENT_BSS_JOIN 137 
#define  QLINK_EVENT_BSS_LEAVE 136 
#define  QLINK_EVENT_EXTERNAL_AUTH 135 
#define  QLINK_EVENT_FREQ_CHANGE 134 
#define  QLINK_EVENT_MGMT_RECEIVED 133 
#define  QLINK_EVENT_RADAR 132 
#define  QLINK_EVENT_SCAN_COMPLETE 131 
#define  QLINK_EVENT_SCAN_RESULTS 130 
#define  QLINK_EVENT_STA_ASSOCIATED 129 
#define  QLINK_EVENT_STA_DEAUTH 128 
 size_t QTNF_MAX_INTF ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  pr_err (char*,size_t) ; 
 int /*<<< orphan*/  pr_warn (char*,int) ; 
 int qtnf_event_handle_bss_join (struct qtnf_vif*,void const*,int) ; 
 int qtnf_event_handle_bss_leave (struct qtnf_vif*,void const*,int) ; 
 int qtnf_event_handle_external_auth (struct qtnf_vif*,void const*,int) ; 
 int qtnf_event_handle_freq_change (struct qtnf_wmac*,void const*,int) ; 
 int qtnf_event_handle_mgmt_received (struct qtnf_vif*,void const*,int) ; 
 int qtnf_event_handle_radar (struct qtnf_vif*,void const*,int) ; 
 int qtnf_event_handle_scan_complete (struct qtnf_wmac*,void const*,int) ; 
 int qtnf_event_handle_scan_results (struct qtnf_vif*,void const*,int) ; 
 int qtnf_event_handle_sta_assoc (struct qtnf_wmac*,struct qtnf_vif*,void const*,int) ; 
 int qtnf_event_handle_sta_deauth (struct qtnf_wmac*,struct qtnf_vif*,void const*,int) ; 

__attribute__((used)) static int qtnf_event_parse(struct qtnf_wmac *mac,
			    const struct sk_buff *event_skb)
{
	const struct qlink_event *event;
	struct qtnf_vif *vif = NULL;
	int ret = -1;
	u16 event_id;
	u16 event_len;

	event = (const struct qlink_event *)event_skb->data;
	event_id = le16_to_cpu(event->event_id);
	event_len = le16_to_cpu(event->mhdr.len);

	if (likely(event->vifid < QTNF_MAX_INTF)) {
		vif = &mac->iflist[event->vifid];
	} else {
		pr_err("invalid vif(%u)\n", event->vifid);
		return -EINVAL;
	}

	switch (event_id) {
	case QLINK_EVENT_STA_ASSOCIATED:
		ret = qtnf_event_handle_sta_assoc(mac, vif, (const void *)event,
						  event_len);
		break;
	case QLINK_EVENT_STA_DEAUTH:
		ret = qtnf_event_handle_sta_deauth(mac, vif,
						   (const void *)event,
						   event_len);
		break;
	case QLINK_EVENT_MGMT_RECEIVED:
		ret = qtnf_event_handle_mgmt_received(vif, (const void *)event,
						      event_len);
		break;
	case QLINK_EVENT_SCAN_RESULTS:
		ret = qtnf_event_handle_scan_results(vif, (const void *)event,
						     event_len);
		break;
	case QLINK_EVENT_SCAN_COMPLETE:
		ret = qtnf_event_handle_scan_complete(mac, (const void *)event,
						      event_len);
		break;
	case QLINK_EVENT_BSS_JOIN:
		ret = qtnf_event_handle_bss_join(vif, (const void *)event,
						 event_len);
		break;
	case QLINK_EVENT_BSS_LEAVE:
		ret = qtnf_event_handle_bss_leave(vif, (const void *)event,
						  event_len);
		break;
	case QLINK_EVENT_FREQ_CHANGE:
		ret = qtnf_event_handle_freq_change(mac, (const void *)event,
						    event_len);
		break;
	case QLINK_EVENT_RADAR:
		ret = qtnf_event_handle_radar(vif, (const void *)event,
					      event_len);
		break;
	case QLINK_EVENT_EXTERNAL_AUTH:
		ret = qtnf_event_handle_external_auth(vif, (const void *)event,
						      event_len);
		break;
	default:
		pr_warn("unknown event type: %x\n", event_id);
		break;
	}

	return ret;
}