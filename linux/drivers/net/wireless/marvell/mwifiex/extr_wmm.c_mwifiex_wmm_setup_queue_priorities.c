#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  size_t u32 ;
typedef  int u16 ;
struct TYPE_4__ {int* queue_priority; } ;
struct mwifiex_private {TYPE_1__ wmm; int /*<<< orphan*/  adapter; int /*<<< orphan*/  wmm_enabled; } ;
struct ieee_types_wmm_parameter {int version; int qos_info_bitmap; int reserved; TYPE_2__* ac_params; } ;
struct TYPE_5__ {int ecw_bitmap; int aci_aifsn_bitmap; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (TYPE_2__*) ; 
 int IEEE80211_WMM_IE_AP_QOSINFO_PARAM_SET_CNT_MASK ; 
 int /*<<< orphan*/  INFO ; 
 int MWIFIEX_ACI ; 
 int MWIFIEX_AIFSN ; 
 int MWIFIEX_ECW_MAX ; 
 int MWIFIEX_ECW_MIN ; 
 int /*<<< orphan*/  mwifiex_dbg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int,int) ; 
 int /*<<< orphan*/  mwifiex_wmm_ac_debug_print (TYPE_2__*) ; 
 int /*<<< orphan*/  mwifiex_wmm_default_queue_priorities (struct mwifiex_private*) ; 
 int /*<<< orphan*/  mwifiex_wmm_queue_priorities_tid (struct mwifiex_private*) ; 
 int /*<<< orphan*/  swap (int,int) ; 
 int* wmm_aci_to_qidx_map ; 

void
mwifiex_wmm_setup_queue_priorities(struct mwifiex_private *priv,
				   struct ieee_types_wmm_parameter *wmm_ie)
{
	u16 cw_min, avg_back_off, tmp[4];
	u32 i, j, num_ac;
	u8 ac_idx;

	if (!wmm_ie || !priv->wmm_enabled) {
		/* WMM is not enabled, just set the defaults and return */
		mwifiex_wmm_default_queue_priorities(priv);
		return;
	}

	mwifiex_dbg(priv->adapter, INFO,
		    "info: WMM Parameter IE: version=%d,\t"
		    "qos_info Parameter Set Count=%d, Reserved=%#x\n",
		    wmm_ie->version, wmm_ie->qos_info_bitmap &
		    IEEE80211_WMM_IE_AP_QOSINFO_PARAM_SET_CNT_MASK,
		    wmm_ie->reserved);

	for (num_ac = 0; num_ac < ARRAY_SIZE(wmm_ie->ac_params); num_ac++) {
		u8 ecw = wmm_ie->ac_params[num_ac].ecw_bitmap;
		u8 aci_aifsn = wmm_ie->ac_params[num_ac].aci_aifsn_bitmap;
		cw_min = (1 << (ecw & MWIFIEX_ECW_MIN)) - 1;
		avg_back_off = (cw_min >> 1) + (aci_aifsn & MWIFIEX_AIFSN);

		ac_idx = wmm_aci_to_qidx_map[(aci_aifsn & MWIFIEX_ACI) >> 5];
		priv->wmm.queue_priority[ac_idx] = ac_idx;
		tmp[ac_idx] = avg_back_off;

		mwifiex_dbg(priv->adapter, INFO,
			    "info: WMM: CWmax=%d CWmin=%d Avg Back-off=%d\n",
			    (1 << ((ecw & MWIFIEX_ECW_MAX) >> 4)) - 1,
			    cw_min, avg_back_off);
		mwifiex_wmm_ac_debug_print(&wmm_ie->ac_params[num_ac]);
	}

	/* Bubble sort */
	for (i = 0; i < num_ac; i++) {
		for (j = 1; j < num_ac - i; j++) {
			if (tmp[j - 1] > tmp[j]) {
				swap(tmp[j - 1], tmp[j]);
				swap(priv->wmm.queue_priority[j - 1],
				     priv->wmm.queue_priority[j]);
			} else if (tmp[j - 1] == tmp[j]) {
				if (priv->wmm.queue_priority[j - 1]
				    < priv->wmm.queue_priority[j])
					swap(priv->wmm.queue_priority[j - 1],
					     priv->wmm.queue_priority[j]);
			}
		}
	}

	mwifiex_wmm_queue_priorities_tid(priv);
}