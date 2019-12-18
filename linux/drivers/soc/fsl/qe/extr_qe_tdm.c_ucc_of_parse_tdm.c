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
typedef  void* u32 ;
struct TYPE_2__ {void* tdm_num; void* tx_sync; void* rx_sync; } ;
struct ucc_tdm_info {TYPE_1__ uf_info; } ;
struct ucc_tdm {int tdm_framer_type; void* siram_entry_id; int /*<<< orphan*/  tdm_mode; void* tdm_port; void* rx_ts_mask; void* tx_ts_mask; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 void* QE_CLK_NONE ; 
 void* QE_RSYNC_PIN ; 
 void* QE_TSYNC_PIN ; 
 int /*<<< orphan*/  TDM_INTERNAL_LOOPBACK ; 
 int /*<<< orphan*/  TDM_NORMAL ; 
 char* of_get_property (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ of_property_read_bool (struct device_node*,char*) ; 
 int of_property_read_u32_index (struct device_node*,char*,int /*<<< orphan*/ ,void**) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 void* qe_clock_source (char const*) ; 
 int /*<<< orphan*/  set_si_param (struct ucc_tdm*,struct ucc_tdm_info*) ; 
 int set_tdm_framer (char const*) ; 

int ucc_of_parse_tdm(struct device_node *np, struct ucc_tdm *utdm,
		     struct ucc_tdm_info *ut_info)
{
	const char *sprop;
	int ret = 0;
	u32 val;

	sprop = of_get_property(np, "fsl,rx-sync-clock", NULL);
	if (sprop) {
		ut_info->uf_info.rx_sync = qe_clock_source(sprop);
		if ((ut_info->uf_info.rx_sync < QE_CLK_NONE) ||
		    (ut_info->uf_info.rx_sync > QE_RSYNC_PIN)) {
			pr_err("QE-TDM: Invalid rx-sync-clock property\n");
			return -EINVAL;
		}
	} else {
		pr_err("QE-TDM: Invalid rx-sync-clock property\n");
		return -EINVAL;
	}

	sprop = of_get_property(np, "fsl,tx-sync-clock", NULL);
	if (sprop) {
		ut_info->uf_info.tx_sync = qe_clock_source(sprop);
		if ((ut_info->uf_info.tx_sync < QE_CLK_NONE) ||
		    (ut_info->uf_info.tx_sync > QE_TSYNC_PIN)) {
			pr_err("QE-TDM: Invalid tx-sync-clock property\n");
		return -EINVAL;
		}
	} else {
		pr_err("QE-TDM: Invalid tx-sync-clock property\n");
		return -EINVAL;
	}

	ret = of_property_read_u32_index(np, "fsl,tx-timeslot-mask", 0, &val);
	if (ret) {
		pr_err("QE-TDM: Invalid tx-timeslot-mask property\n");
		return -EINVAL;
	}
	utdm->tx_ts_mask = val;

	ret = of_property_read_u32_index(np, "fsl,rx-timeslot-mask", 0, &val);
	if (ret) {
		ret = -EINVAL;
		pr_err("QE-TDM: Invalid rx-timeslot-mask property\n");
		return ret;
	}
	utdm->rx_ts_mask = val;

	ret = of_property_read_u32_index(np, "fsl,tdm-id", 0, &val);
	if (ret) {
		ret = -EINVAL;
		pr_err("QE-TDM: No fsl,tdm-id property for this UCC\n");
		return ret;
	}
	utdm->tdm_port = val;
	ut_info->uf_info.tdm_num = utdm->tdm_port;

	if (of_property_read_bool(np, "fsl,tdm-internal-loopback"))
		utdm->tdm_mode = TDM_INTERNAL_LOOPBACK;
	else
		utdm->tdm_mode = TDM_NORMAL;

	sprop = of_get_property(np, "fsl,tdm-framer-type", NULL);
	if (!sprop) {
		ret = -EINVAL;
		pr_err("QE-TDM: No tdm-framer-type property for UCC\n");
		return ret;
	}
	ret = set_tdm_framer(sprop);
	if (ret < 0)
		return -EINVAL;
	utdm->tdm_framer_type = ret;

	ret = of_property_read_u32_index(np, "fsl,siram-entry-id", 0, &val);
	if (ret) {
		ret = -EINVAL;
		pr_err("QE-TDM: No siram entry id for UCC\n");
		return ret;
	}
	utdm->siram_entry_id = val;

	set_si_param(utdm, ut_info);
	return ret;
}