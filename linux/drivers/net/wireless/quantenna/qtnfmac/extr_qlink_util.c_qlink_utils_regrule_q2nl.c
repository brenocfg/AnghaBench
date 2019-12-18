#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct qlink_tlv_reg_rule {int /*<<< orphan*/  flags; int /*<<< orphan*/  dfs_cac_ms; int /*<<< orphan*/  max_eirp; int /*<<< orphan*/  max_antenna_gain; int /*<<< orphan*/  max_bandwidth_khz; int /*<<< orphan*/  end_freq_khz; int /*<<< orphan*/  start_freq_khz; } ;
struct TYPE_3__ {void* max_eirp; void* max_antenna_gain; } ;
struct TYPE_4__ {void* max_bandwidth_khz; void* end_freq_khz; void* start_freq_khz; } ;
struct ieee80211_reg_rule {int /*<<< orphan*/  flags; void* dfs_cac_ms; TYPE_1__ power_rule; TYPE_2__ freq_range; } ;

/* Variables and functions */
 void* le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qtnf_reg_rule_flags_parse (void*) ; 

void qlink_utils_regrule_q2nl(struct ieee80211_reg_rule *rule,
			      const struct qlink_tlv_reg_rule *tlv)
{
	rule->freq_range.start_freq_khz = le32_to_cpu(tlv->start_freq_khz);
	rule->freq_range.end_freq_khz = le32_to_cpu(tlv->end_freq_khz);
	rule->freq_range.max_bandwidth_khz =
		le32_to_cpu(tlv->max_bandwidth_khz);
	rule->power_rule.max_antenna_gain = le32_to_cpu(tlv->max_antenna_gain);
	rule->power_rule.max_eirp = le32_to_cpu(tlv->max_eirp);
	rule->dfs_cac_ms = le32_to_cpu(tlv->dfs_cac_ms);
	rule->flags = qtnf_reg_rule_flags_parse(le32_to_cpu(tlv->flags));
}