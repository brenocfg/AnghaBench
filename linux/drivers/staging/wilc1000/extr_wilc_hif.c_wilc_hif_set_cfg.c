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
typedef  int /*<<< orphan*/  u16 ;
struct wilc_vif {int dummy; } ;
struct wid {int size; void* type; int /*<<< orphan*/ * val; int /*<<< orphan*/  id; } ;
struct cfg_param_attr {int flag; int /*<<< orphan*/  rts_threshold; int /*<<< orphan*/  frag_threshold; int /*<<< orphan*/  long_retry_limit; int /*<<< orphan*/  short_retry_limit; } ;
typedef  int /*<<< orphan*/  s8 ;

/* Variables and functions */
 int /*<<< orphan*/  WID_FRAG_THRESHOLD ; 
 int /*<<< orphan*/  WID_LONG_RETRY_LIMIT ; 
 int /*<<< orphan*/  WID_RTS_THRESHOLD ; 
 void* WID_SHORT ; 
 int /*<<< orphan*/  WID_SHORT_RETRY_LIMIT ; 
 int WILC_CFG_PARAM_FRAG_THRESHOLD ; 
 int WILC_CFG_PARAM_RETRY_LONG ; 
 int WILC_CFG_PARAM_RETRY_SHORT ; 
 int WILC_CFG_PARAM_RTS_THRESHOLD ; 
 int /*<<< orphan*/  WILC_SET_CFG ; 
 int wilc_send_config_pkt (struct wilc_vif*,int /*<<< orphan*/ ,struct wid*,int) ; 

int wilc_hif_set_cfg(struct wilc_vif *vif, struct cfg_param_attr *param)
{
	struct wid wid_list[4];
	int i = 0;

	if (param->flag & WILC_CFG_PARAM_RETRY_SHORT) {
		wid_list[i].id = WID_SHORT_RETRY_LIMIT;
		wid_list[i].val = (s8 *)&param->short_retry_limit;
		wid_list[i].type = WID_SHORT;
		wid_list[i].size = sizeof(u16);
		i++;
	}
	if (param->flag & WILC_CFG_PARAM_RETRY_LONG) {
		wid_list[i].id = WID_LONG_RETRY_LIMIT;
		wid_list[i].val = (s8 *)&param->long_retry_limit;
		wid_list[i].type = WID_SHORT;
		wid_list[i].size = sizeof(u16);
		i++;
	}
	if (param->flag & WILC_CFG_PARAM_FRAG_THRESHOLD) {
		wid_list[i].id = WID_FRAG_THRESHOLD;
		wid_list[i].val = (s8 *)&param->frag_threshold;
		wid_list[i].type = WID_SHORT;
		wid_list[i].size = sizeof(u16);
		i++;
	}
	if (param->flag & WILC_CFG_PARAM_RTS_THRESHOLD) {
		wid_list[i].id = WID_RTS_THRESHOLD;
		wid_list[i].val = (s8 *)&param->rts_threshold;
		wid_list[i].type = WID_SHORT;
		wid_list[i].size = sizeof(u16);
		i++;
	}

	return wilc_send_config_pkt(vif, WILC_SET_CFG, wid_list, i);
}