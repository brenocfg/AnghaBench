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
struct tc_configuration {scalar_t__ dcb_pfc; TYPE_1__* path; } ;
struct ixgbe_dcb_config {scalar_t__** bw_percentage; scalar_t__ pfc_mode_enable; struct tc_configuration* tc_config; } ;
struct ixgbe_adapter {struct ixgbe_dcb_config dcb_cfg; struct ixgbe_dcb_config temp_dcb_cfg; } ;
struct TYPE_2__ {scalar_t__ prio_type; scalar_t__ bwg_id; scalar_t__ bwg_percent; scalar_t__ up_to_tc_bitmap; } ;

/* Variables and functions */
 int BIT_APP_UPCHG ; 
 int BIT_PFC ; 
 int BIT_PG_RX ; 
 int BIT_PG_TX ; 
 int DCB_PFC_UP_ATTR_0 ; 
 int DCB_PFC_UP_ATTR_MAX ; 
 int DCB_PG_ATTR_BW_ID_0 ; 
 int DCB_PG_ATTR_BW_ID_MAX ; 
 int DCB_PG_ATTR_TC_0 ; 
 int DCB_RX_CONFIG ; 
 int DCB_TX_CONFIG ; 

__attribute__((used)) static int ixgbe_copy_dcb_cfg(struct ixgbe_adapter *adapter, int tc_max)
{
	struct ixgbe_dcb_config *scfg = &adapter->temp_dcb_cfg;
	struct ixgbe_dcb_config *dcfg = &adapter->dcb_cfg;
	struct tc_configuration *src = NULL;
	struct tc_configuration *dst = NULL;
	int i, j;
	int tx = DCB_TX_CONFIG;
	int rx = DCB_RX_CONFIG;
	int changes = 0;
#ifdef IXGBE_FCOE
	struct dcb_app app = {
			      .selector = DCB_APP_IDTYPE_ETHTYPE,
			      .protocol = ETH_P_FCOE,
			     };
	u8 up = dcb_getapp(adapter->netdev, &app);

	if (up && !(up & BIT(adapter->fcoe.up)))
		changes |= BIT_APP_UPCHG;
#endif

	for (i = DCB_PG_ATTR_TC_0; i < tc_max + DCB_PG_ATTR_TC_0; i++) {
		src = &scfg->tc_config[i - DCB_PG_ATTR_TC_0];
		dst = &dcfg->tc_config[i - DCB_PG_ATTR_TC_0];

		if (dst->path[tx].prio_type != src->path[tx].prio_type) {
			dst->path[tx].prio_type = src->path[tx].prio_type;
			changes |= BIT_PG_TX;
		}

		if (dst->path[tx].bwg_id != src->path[tx].bwg_id) {
			dst->path[tx].bwg_id = src->path[tx].bwg_id;
			changes |= BIT_PG_TX;
		}

		if (dst->path[tx].bwg_percent != src->path[tx].bwg_percent) {
			dst->path[tx].bwg_percent = src->path[tx].bwg_percent;
			changes |= BIT_PG_TX;
		}

		if (dst->path[tx].up_to_tc_bitmap !=
				src->path[tx].up_to_tc_bitmap) {
			dst->path[tx].up_to_tc_bitmap =
				src->path[tx].up_to_tc_bitmap;
			changes |= (BIT_PG_TX | BIT_PFC | BIT_APP_UPCHG);
		}

		if (dst->path[rx].prio_type != src->path[rx].prio_type) {
			dst->path[rx].prio_type = src->path[rx].prio_type;
			changes |= BIT_PG_RX;
		}

		if (dst->path[rx].bwg_id != src->path[rx].bwg_id) {
			dst->path[rx].bwg_id = src->path[rx].bwg_id;
			changes |= BIT_PG_RX;
		}

		if (dst->path[rx].bwg_percent != src->path[rx].bwg_percent) {
			dst->path[rx].bwg_percent = src->path[rx].bwg_percent;
			changes |= BIT_PG_RX;
		}

		if (dst->path[rx].up_to_tc_bitmap !=
				src->path[rx].up_to_tc_bitmap) {
			dst->path[rx].up_to_tc_bitmap =
				src->path[rx].up_to_tc_bitmap;
			changes |= (BIT_PG_RX | BIT_PFC | BIT_APP_UPCHG);
		}
	}

	for (i = DCB_PG_ATTR_BW_ID_0; i < DCB_PG_ATTR_BW_ID_MAX; i++) {
		j = i - DCB_PG_ATTR_BW_ID_0;
		if (dcfg->bw_percentage[tx][j] != scfg->bw_percentage[tx][j]) {
			dcfg->bw_percentage[tx][j] = scfg->bw_percentage[tx][j];
			changes |= BIT_PG_TX;
		}
		if (dcfg->bw_percentage[rx][j] != scfg->bw_percentage[rx][j]) {
			dcfg->bw_percentage[rx][j] = scfg->bw_percentage[rx][j];
			changes |= BIT_PG_RX;
		}
	}

	for (i = DCB_PFC_UP_ATTR_0; i < DCB_PFC_UP_ATTR_MAX; i++) {
		j = i - DCB_PFC_UP_ATTR_0;
		if (dcfg->tc_config[j].dcb_pfc != scfg->tc_config[j].dcb_pfc) {
			dcfg->tc_config[j].dcb_pfc = scfg->tc_config[j].dcb_pfc;
			changes |= BIT_PFC;
		}
	}

	if (dcfg->pfc_mode_enable != scfg->pfc_mode_enable) {
		dcfg->pfc_mode_enable = scfg->pfc_mode_enable;
		changes |= BIT_PFC;
	}

	return changes;
}