#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct qtnf_vif {int /*<<< orphan*/  vifid; TYPE_2__* mac; } ;
struct qlink_tlv_hdr {int dummy; } ;
struct qlink_tlv_chandef {int dummy; } ;
struct qlink_cmd_start_ap {int dummy; } ;
struct qlink_cmd {int dummy; } ;
struct TYPE_4__ {scalar_t__ probe_resp_len; scalar_t__ assocresp_ies_len; scalar_t__ proberesp_ies_len; scalar_t__ beacon_ies_len; scalar_t__ tail_len; scalar_t__ head_len; } ;
struct cfg80211_ap_settings {TYPE_3__* acl; int /*<<< orphan*/  chandef; TYPE_1__ beacon; scalar_t__ ssid_len; } ;
struct TYPE_6__ {int /*<<< orphan*/  n_acl_entries; } ;
struct TYPE_5__ {int /*<<< orphan*/  macid; } ;

/* Variables and functions */
 int QTNF_MAX_CMD_BUF_SIZE ; 
 scalar_t__ cfg80211_chandef_valid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mac_addrs ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 scalar_t__ struct_size (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool qtnf_cmd_start_ap_can_fit(const struct qtnf_vif *vif,
				      const struct cfg80211_ap_settings *s)
{
	unsigned int len = sizeof(struct qlink_cmd_start_ap);

	len += s->ssid_len;
	len += s->beacon.head_len;
	len += s->beacon.tail_len;
	len += s->beacon.beacon_ies_len;
	len += s->beacon.proberesp_ies_len;
	len += s->beacon.assocresp_ies_len;
	len += s->beacon.probe_resp_len;

	if (cfg80211_chandef_valid(&s->chandef))
		len += sizeof(struct qlink_tlv_chandef);

	if (s->acl)
		len += sizeof(struct qlink_tlv_hdr) +
		       struct_size(s->acl, mac_addrs, s->acl->n_acl_entries);

	if (len > (sizeof(struct qlink_cmd) + QTNF_MAX_CMD_BUF_SIZE)) {
		pr_err("VIF%u.%u: can not fit AP settings: %u\n",
		       vif->mac->macid, vif->vifid, len);
		return false;
	}

	return true;
}