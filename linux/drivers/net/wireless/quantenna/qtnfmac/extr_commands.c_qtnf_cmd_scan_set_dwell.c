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
typedef  scalar_t__ u16 ;
struct sk_buff {int dummy; } ;
struct qtnf_wmac {int /*<<< orphan*/  macid; struct cfg80211_scan_request* scan_req; } ;
struct cfg80211_scan_request {scalar_t__ duration_mandatory; scalar_t__ duration; } ;

/* Variables and functions */
 scalar_t__ QTNF_SCAN_DWELL_ACTIVE_DEFAULT ; 
 scalar_t__ QTNF_SCAN_DWELL_PASSIVE_DEFAULT ; 
 scalar_t__ QTNF_SCAN_SAMPLE_DURATION_DEFAULT ; 
 int /*<<< orphan*/  QTN_TLV_ID_SCAN_DWELL_ACTIVE ; 
 int /*<<< orphan*/  QTN_TLV_ID_SCAN_DWELL_PASSIVE ; 
 int /*<<< orphan*/  QTN_TLV_ID_SCAN_SAMPLE_DURATION ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,char*,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  qtnf_cmd_skb_put_tlv_u16 (struct sk_buff*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void qtnf_cmd_scan_set_dwell(struct qtnf_wmac *mac,
				    struct sk_buff *cmd_skb)
{
	struct cfg80211_scan_request *scan_req = mac->scan_req;
	u16 dwell_active = QTNF_SCAN_DWELL_ACTIVE_DEFAULT;
	u16 dwell_passive = QTNF_SCAN_DWELL_PASSIVE_DEFAULT;
	u16 duration = QTNF_SCAN_SAMPLE_DURATION_DEFAULT;

	if (scan_req->duration) {
		dwell_active = scan_req->duration;
		dwell_passive = scan_req->duration;
	}

	pr_debug("MAC%u: %s scan dwell active=%u, passive=%u, duration=%u\n",
		 mac->macid,
		 scan_req->duration_mandatory ? "mandatory" : "max",
		 dwell_active, dwell_passive, duration);

	qtnf_cmd_skb_put_tlv_u16(cmd_skb,
				 QTN_TLV_ID_SCAN_DWELL_ACTIVE,
				 dwell_active);
	qtnf_cmd_skb_put_tlv_u16(cmd_skb,
				 QTN_TLV_ID_SCAN_DWELL_PASSIVE,
				 dwell_passive);
	qtnf_cmd_skb_put_tlv_u16(cmd_skb,
				 QTN_TLV_ID_SCAN_SAMPLE_DURATION,
				 duration);
}