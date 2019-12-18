#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_34__   TYPE_9__ ;
typedef  struct TYPE_33__   TYPE_8__ ;
typedef  struct TYPE_32__   TYPE_7__ ;
typedef  struct TYPE_31__   TYPE_6__ ;
typedef  struct TYPE_30__   TYPE_5__ ;
typedef  struct TYPE_29__   TYPE_4__ ;
typedef  struct TYPE_28__   TYPE_3__ ;
typedef  struct TYPE_27__   TYPE_2__ ;
typedef  struct TYPE_26__   TYPE_1__ ;
typedef  struct TYPE_25__   TYPE_17__ ;
typedef  struct TYPE_24__   TYPE_16__ ;
typedef  struct TYPE_23__   TYPE_15__ ;
typedef  struct TYPE_22__   TYPE_14__ ;
typedef  struct TYPE_21__   TYPE_13__ ;
typedef  struct TYPE_20__   TYPE_12__ ;
typedef  struct TYPE_19__   TYPE_11__ ;
typedef  struct TYPE_18__   TYPE_10__ ;

/* Type definitions */
struct TYPE_24__ {int* port_bs_flag; } ;
struct TYPE_25__ {TYPE_16__ MacStat; } ;
struct TYPE_19__ {int /*<<< orphan*/ * port_lem_cts; int /*<<< orphan*/ * port_lem_reject_cts; int /*<<< orphan*/ * port_lct_fail_cts; int /*<<< orphan*/  mac_lost_cts; int /*<<< orphan*/  mac_error_cts; int /*<<< orphan*/  mac_transmit_cts; int /*<<< orphan*/  mac_copied_cts; int /*<<< orphan*/  mac_frame_cts; int /*<<< orphan*/ * port_hardware_present; int /*<<< orphan*/ * port_ler_flag; int /*<<< orphan*/ * port_pc_withhold; int /*<<< orphan*/ * port_pcm_state; int /*<<< orphan*/ * port_connect_state; int /*<<< orphan*/ * port_ler_alarm; int /*<<< orphan*/ * port_ler_cutoff; int /*<<< orphan*/ * port_ler_estimate; int /*<<< orphan*/ * port_bs_flag; int /*<<< orphan*/ * port_connection_capabilities; int /*<<< orphan*/ * port_pmd_class; int /*<<< orphan*/ * port_available_paths; int /*<<< orphan*/ * port_mac_placement; int /*<<< orphan*/ * port_requested_paths; int /*<<< orphan*/ * port_current_path; int /*<<< orphan*/ * port_mac_indicated; int /*<<< orphan*/ * port_connection_policies; int /*<<< orphan*/ * port_neighbor_type; int /*<<< orphan*/ * port_my_type; int /*<<< orphan*/ * path_configuration; int /*<<< orphan*/  path_max_t_req; int /*<<< orphan*/  path_t_max_lower_bound; int /*<<< orphan*/  path_tvx_lower_bound; int /*<<< orphan*/  mac_ma_unitdata_enable; int /*<<< orphan*/  mac_hardware_present; int /*<<< orphan*/  mac_ma_unitdata_available; int /*<<< orphan*/  mac_frame_error_flag; int /*<<< orphan*/  mac_una_da_flag; int /*<<< orphan*/  mac_da_flag; int /*<<< orphan*/  mac_rmt_state; int /*<<< orphan*/  mac_frame_error_ratio; int /*<<< orphan*/  mac_frame_error_threshold; int /*<<< orphan*/  mac_tvx_value; int /*<<< orphan*/  mac_t_max; int /*<<< orphan*/  mac_t_neg; int /*<<< orphan*/  mac_t_req; int /*<<< orphan*/ * mac_smt_address; int /*<<< orphan*/  mac_downstream_port_type; int /*<<< orphan*/  mac_requested_paths; int /*<<< orphan*/  mac_dup_address_test; int /*<<< orphan*/ * mac_old_downstream_nbr; int /*<<< orphan*/ * mac_old_upstream_nbr; int /*<<< orphan*/ * mac_downstream_nbr; int /*<<< orphan*/ * mac_upstream_nbr; int /*<<< orphan*/  mac_current_path; int /*<<< orphan*/  mac_available_paths; int /*<<< orphan*/  mac_tvx_capability; int /*<<< orphan*/  mac_t_max_capability; int /*<<< orphan*/  mac_frame_status_functions; int /*<<< orphan*/  smt_transition_time_stamp; int /*<<< orphan*/  smt_time_stamp; int /*<<< orphan*/  smt_peer_wrap_flag; int /*<<< orphan*/  smt_station_status; int /*<<< orphan*/  smt_remote_disconnect_flag; int /*<<< orphan*/  smt_cf_state; int /*<<< orphan*/  smt_ecm_state; int /*<<< orphan*/  smt_bypass_present; int /*<<< orphan*/  smt_trace_max_expiration; int /*<<< orphan*/  smt_stat_rpt_policy; int /*<<< orphan*/  smt_t_notify; int /*<<< orphan*/  smt_connection_policy; int /*<<< orphan*/  smt_config_policy; int /*<<< orphan*/  smt_config_capabilities; int /*<<< orphan*/  smt_available_paths; int /*<<< orphan*/  smt_master_cts; int /*<<< orphan*/  smt_non_master_cts; int /*<<< orphan*/  smt_mac_cts; int /*<<< orphan*/  smt_mib_version_id; int /*<<< orphan*/ * smt_user_data; int /*<<< orphan*/  smt_lo_version_id; int /*<<< orphan*/  smt_hi_version_id; int /*<<< orphan*/  smt_op_version_id; int /*<<< orphan*/ * smt_station_id; } ;
struct s_smc {TYPE_17__ os; TYPE_15__* cmd_rsp_virt; TYPE_11__ stats; } ;
struct net_device_stats {int dummy; } ;
struct net_device {int dummy; } ;
struct TYPE_34__ {int /*<<< orphan*/  ls; } ;
struct TYPE_33__ {int /*<<< orphan*/  ls; } ;
struct TYPE_32__ {int /*<<< orphan*/  ls; } ;
struct TYPE_31__ {int /*<<< orphan*/  ls; } ;
struct TYPE_30__ {int /*<<< orphan*/  ls; } ;
struct TYPE_29__ {int /*<<< orphan*/  ls; } ;
struct TYPE_27__ {int /*<<< orphan*/  ls; } ;
struct TYPE_26__ {int /*<<< orphan*/  ls; } ;
struct TYPE_28__ {int /*<<< orphan*/ * port_hardware_present; int /*<<< orphan*/ * port_ler_flag; int /*<<< orphan*/ * port_pc_withhold; int /*<<< orphan*/ * port_pcm_state; int /*<<< orphan*/ * port_connect_state; int /*<<< orphan*/ * port_ler_alarm; int /*<<< orphan*/ * port_ler_cutoff; int /*<<< orphan*/ * port_ler_estimate; int /*<<< orphan*/ * port_bs_flag; int /*<<< orphan*/ * port_connection_capabilities; int /*<<< orphan*/ * port_pmd_class; int /*<<< orphan*/ * port_available_paths; int /*<<< orphan*/ * port_mac_placement; int /*<<< orphan*/ * port_requested_paths; int /*<<< orphan*/ * port_current_path; int /*<<< orphan*/ * port_mac_indicated; int /*<<< orphan*/ * port_connection_policies; int /*<<< orphan*/ * port_neighbor_type; int /*<<< orphan*/ * port_my_type; int /*<<< orphan*/  path_configuration; int /*<<< orphan*/  path_max_t_req; int /*<<< orphan*/  path_t_max_lower_bound; int /*<<< orphan*/  path_tvx_lower_bound; int /*<<< orphan*/  mac_ma_unitdata_enable; int /*<<< orphan*/  mac_hardware_present; int /*<<< orphan*/  mac_ma_unitdata_available; int /*<<< orphan*/  mac_frame_error_flag; int /*<<< orphan*/  mac_unda_flag; int /*<<< orphan*/  mac_da_flag; int /*<<< orphan*/  mac_rmt_state; int /*<<< orphan*/  mac_frame_error_ratio; int /*<<< orphan*/  mac_frame_error_threshold; int /*<<< orphan*/  mac_tvx_value; int /*<<< orphan*/  mac_t_max; int /*<<< orphan*/  mac_t_neg; int /*<<< orphan*/  mac_t_req; int /*<<< orphan*/  mac_smt_address; int /*<<< orphan*/  mac_downstream_port_type; int /*<<< orphan*/  mac_requested_paths; int /*<<< orphan*/  mac_dup_address_test; int /*<<< orphan*/  mac_old_downstream_nbr; int /*<<< orphan*/  mac_old_upstream_nbr; int /*<<< orphan*/  mac_downstream_nbr; int /*<<< orphan*/  mac_upstream_nbr; int /*<<< orphan*/  mac_current_path; int /*<<< orphan*/  mac_available_paths; int /*<<< orphan*/  mac_tvx_capability; int /*<<< orphan*/  mac_t_max_capability; int /*<<< orphan*/  mac_frame_status_functions; TYPE_2__ smt_transition_time_stamp; TYPE_1__ smt_msg_time_stamp; int /*<<< orphan*/  smt_peer_wrap_flag; int /*<<< orphan*/  smt_station_status; int /*<<< orphan*/  smt_remote_disconnect_flag; int /*<<< orphan*/  smt_cf_state; int /*<<< orphan*/  smt_ecm_state; int /*<<< orphan*/  smt_bypass_present; int /*<<< orphan*/  smt_trace_max_expiration; int /*<<< orphan*/  smt_stat_rpt_policy; int /*<<< orphan*/  smt_t_notify; int /*<<< orphan*/  smt_connection_policy; int /*<<< orphan*/  smt_config_policy; int /*<<< orphan*/  smt_config_capabilities; int /*<<< orphan*/  smt_available_paths; int /*<<< orphan*/  smt_master_ct; int /*<<< orphan*/  smt_non_master_ct; int /*<<< orphan*/  smt_mac_ct; int /*<<< orphan*/  smt_mib_version_id; int /*<<< orphan*/  smt_user_data; int /*<<< orphan*/  smt_lo_version_id; int /*<<< orphan*/  smt_hi_version_id; int /*<<< orphan*/  smt_op_version_id; int /*<<< orphan*/  smt_station_id; } ;
struct TYPE_21__ {TYPE_12__* link_errors; TYPE_10__* lem_rejects; TYPE_9__* lct_rejects; TYPE_8__ lost_cnt; TYPE_7__ error_cnt; TYPE_6__ transmit_cnt; TYPE_5__ copied_cnt; TYPE_4__ frame_cnt; } ;
struct TYPE_22__ {TYPE_13__ cntrs; } ;
struct TYPE_23__ {TYPE_14__ cntrs_get; TYPE_3__ smt_mib_get; } ;
struct TYPE_20__ {int /*<<< orphan*/  ls; } ;
struct TYPE_18__ {int /*<<< orphan*/  ls; } ;

/* Variables and functions */
 int FDDI_K_ALEN ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 struct s_smc* netdev_priv (struct net_device*) ; 

__attribute__((used)) static struct net_device_stats *skfp_ctl_get_stats(struct net_device *dev)
{
	struct s_smc *bp = netdev_priv(dev);

	/* Fill the bp->stats structure with driver-maintained counters */

	bp->os.MacStat.port_bs_flag[0] = 0x1234;
	bp->os.MacStat.port_bs_flag[1] = 0x5678;
// goos: need to fill out fddi statistic
#if 0
	/* Get FDDI SMT MIB objects */

/* Fill the bp->stats structure with the SMT MIB object values */

	memcpy(bp->stats.smt_station_id, &bp->cmd_rsp_virt->smt_mib_get.smt_station_id, sizeof(bp->cmd_rsp_virt->smt_mib_get.smt_station_id));
	bp->stats.smt_op_version_id = bp->cmd_rsp_virt->smt_mib_get.smt_op_version_id;
	bp->stats.smt_hi_version_id = bp->cmd_rsp_virt->smt_mib_get.smt_hi_version_id;
	bp->stats.smt_lo_version_id = bp->cmd_rsp_virt->smt_mib_get.smt_lo_version_id;
	memcpy(bp->stats.smt_user_data, &bp->cmd_rsp_virt->smt_mib_get.smt_user_data, sizeof(bp->cmd_rsp_virt->smt_mib_get.smt_user_data));
	bp->stats.smt_mib_version_id = bp->cmd_rsp_virt->smt_mib_get.smt_mib_version_id;
	bp->stats.smt_mac_cts = bp->cmd_rsp_virt->smt_mib_get.smt_mac_ct;
	bp->stats.smt_non_master_cts = bp->cmd_rsp_virt->smt_mib_get.smt_non_master_ct;
	bp->stats.smt_master_cts = bp->cmd_rsp_virt->smt_mib_get.smt_master_ct;
	bp->stats.smt_available_paths = bp->cmd_rsp_virt->smt_mib_get.smt_available_paths;
	bp->stats.smt_config_capabilities = bp->cmd_rsp_virt->smt_mib_get.smt_config_capabilities;
	bp->stats.smt_config_policy = bp->cmd_rsp_virt->smt_mib_get.smt_config_policy;
	bp->stats.smt_connection_policy = bp->cmd_rsp_virt->smt_mib_get.smt_connection_policy;
	bp->stats.smt_t_notify = bp->cmd_rsp_virt->smt_mib_get.smt_t_notify;
	bp->stats.smt_stat_rpt_policy = bp->cmd_rsp_virt->smt_mib_get.smt_stat_rpt_policy;
	bp->stats.smt_trace_max_expiration = bp->cmd_rsp_virt->smt_mib_get.smt_trace_max_expiration;
	bp->stats.smt_bypass_present = bp->cmd_rsp_virt->smt_mib_get.smt_bypass_present;
	bp->stats.smt_ecm_state = bp->cmd_rsp_virt->smt_mib_get.smt_ecm_state;
	bp->stats.smt_cf_state = bp->cmd_rsp_virt->smt_mib_get.smt_cf_state;
	bp->stats.smt_remote_disconnect_flag = bp->cmd_rsp_virt->smt_mib_get.smt_remote_disconnect_flag;
	bp->stats.smt_station_status = bp->cmd_rsp_virt->smt_mib_get.smt_station_status;
	bp->stats.smt_peer_wrap_flag = bp->cmd_rsp_virt->smt_mib_get.smt_peer_wrap_flag;
	bp->stats.smt_time_stamp = bp->cmd_rsp_virt->smt_mib_get.smt_msg_time_stamp.ls;
	bp->stats.smt_transition_time_stamp = bp->cmd_rsp_virt->smt_mib_get.smt_transition_time_stamp.ls;
	bp->stats.mac_frame_status_functions = bp->cmd_rsp_virt->smt_mib_get.mac_frame_status_functions;
	bp->stats.mac_t_max_capability = bp->cmd_rsp_virt->smt_mib_get.mac_t_max_capability;
	bp->stats.mac_tvx_capability = bp->cmd_rsp_virt->smt_mib_get.mac_tvx_capability;
	bp->stats.mac_available_paths = bp->cmd_rsp_virt->smt_mib_get.mac_available_paths;
	bp->stats.mac_current_path = bp->cmd_rsp_virt->smt_mib_get.mac_current_path;
	memcpy(bp->stats.mac_upstream_nbr, &bp->cmd_rsp_virt->smt_mib_get.mac_upstream_nbr, FDDI_K_ALEN);
	memcpy(bp->stats.mac_downstream_nbr, &bp->cmd_rsp_virt->smt_mib_get.mac_downstream_nbr, FDDI_K_ALEN);
	memcpy(bp->stats.mac_old_upstream_nbr, &bp->cmd_rsp_virt->smt_mib_get.mac_old_upstream_nbr, FDDI_K_ALEN);
	memcpy(bp->stats.mac_old_downstream_nbr, &bp->cmd_rsp_virt->smt_mib_get.mac_old_downstream_nbr, FDDI_K_ALEN);
	bp->stats.mac_dup_address_test = bp->cmd_rsp_virt->smt_mib_get.mac_dup_address_test;
	bp->stats.mac_requested_paths = bp->cmd_rsp_virt->smt_mib_get.mac_requested_paths;
	bp->stats.mac_downstream_port_type = bp->cmd_rsp_virt->smt_mib_get.mac_downstream_port_type;
	memcpy(bp->stats.mac_smt_address, &bp->cmd_rsp_virt->smt_mib_get.mac_smt_address, FDDI_K_ALEN);
	bp->stats.mac_t_req = bp->cmd_rsp_virt->smt_mib_get.mac_t_req;
	bp->stats.mac_t_neg = bp->cmd_rsp_virt->smt_mib_get.mac_t_neg;
	bp->stats.mac_t_max = bp->cmd_rsp_virt->smt_mib_get.mac_t_max;
	bp->stats.mac_tvx_value = bp->cmd_rsp_virt->smt_mib_get.mac_tvx_value;
	bp->stats.mac_frame_error_threshold = bp->cmd_rsp_virt->smt_mib_get.mac_frame_error_threshold;
	bp->stats.mac_frame_error_ratio = bp->cmd_rsp_virt->smt_mib_get.mac_frame_error_ratio;
	bp->stats.mac_rmt_state = bp->cmd_rsp_virt->smt_mib_get.mac_rmt_state;
	bp->stats.mac_da_flag = bp->cmd_rsp_virt->smt_mib_get.mac_da_flag;
	bp->stats.mac_una_da_flag = bp->cmd_rsp_virt->smt_mib_get.mac_unda_flag;
	bp->stats.mac_frame_error_flag = bp->cmd_rsp_virt->smt_mib_get.mac_frame_error_flag;
	bp->stats.mac_ma_unitdata_available = bp->cmd_rsp_virt->smt_mib_get.mac_ma_unitdata_available;
	bp->stats.mac_hardware_present = bp->cmd_rsp_virt->smt_mib_get.mac_hardware_present;
	bp->stats.mac_ma_unitdata_enable = bp->cmd_rsp_virt->smt_mib_get.mac_ma_unitdata_enable;
	bp->stats.path_tvx_lower_bound = bp->cmd_rsp_virt->smt_mib_get.path_tvx_lower_bound;
	bp->stats.path_t_max_lower_bound = bp->cmd_rsp_virt->smt_mib_get.path_t_max_lower_bound;
	bp->stats.path_max_t_req = bp->cmd_rsp_virt->smt_mib_get.path_max_t_req;
	memcpy(bp->stats.path_configuration, &bp->cmd_rsp_virt->smt_mib_get.path_configuration, sizeof(bp->cmd_rsp_virt->smt_mib_get.path_configuration));
	bp->stats.port_my_type[0] = bp->cmd_rsp_virt->smt_mib_get.port_my_type[0];
	bp->stats.port_my_type[1] = bp->cmd_rsp_virt->smt_mib_get.port_my_type[1];
	bp->stats.port_neighbor_type[0] = bp->cmd_rsp_virt->smt_mib_get.port_neighbor_type[0];
	bp->stats.port_neighbor_type[1] = bp->cmd_rsp_virt->smt_mib_get.port_neighbor_type[1];
	bp->stats.port_connection_policies[0] = bp->cmd_rsp_virt->smt_mib_get.port_connection_policies[0];
	bp->stats.port_connection_policies[1] = bp->cmd_rsp_virt->smt_mib_get.port_connection_policies[1];
	bp->stats.port_mac_indicated[0] = bp->cmd_rsp_virt->smt_mib_get.port_mac_indicated[0];
	bp->stats.port_mac_indicated[1] = bp->cmd_rsp_virt->smt_mib_get.port_mac_indicated[1];
	bp->stats.port_current_path[0] = bp->cmd_rsp_virt->smt_mib_get.port_current_path[0];
	bp->stats.port_current_path[1] = bp->cmd_rsp_virt->smt_mib_get.port_current_path[1];
	memcpy(&bp->stats.port_requested_paths[0 * 3], &bp->cmd_rsp_virt->smt_mib_get.port_requested_paths[0], 3);
	memcpy(&bp->stats.port_requested_paths[1 * 3], &bp->cmd_rsp_virt->smt_mib_get.port_requested_paths[1], 3);
	bp->stats.port_mac_placement[0] = bp->cmd_rsp_virt->smt_mib_get.port_mac_placement[0];
	bp->stats.port_mac_placement[1] = bp->cmd_rsp_virt->smt_mib_get.port_mac_placement[1];
	bp->stats.port_available_paths[0] = bp->cmd_rsp_virt->smt_mib_get.port_available_paths[0];
	bp->stats.port_available_paths[1] = bp->cmd_rsp_virt->smt_mib_get.port_available_paths[1];
	bp->stats.port_pmd_class[0] = bp->cmd_rsp_virt->smt_mib_get.port_pmd_class[0];
	bp->stats.port_pmd_class[1] = bp->cmd_rsp_virt->smt_mib_get.port_pmd_class[1];
	bp->stats.port_connection_capabilities[0] = bp->cmd_rsp_virt->smt_mib_get.port_connection_capabilities[0];
	bp->stats.port_connection_capabilities[1] = bp->cmd_rsp_virt->smt_mib_get.port_connection_capabilities[1];
	bp->stats.port_bs_flag[0] = bp->cmd_rsp_virt->smt_mib_get.port_bs_flag[0];
	bp->stats.port_bs_flag[1] = bp->cmd_rsp_virt->smt_mib_get.port_bs_flag[1];
	bp->stats.port_ler_estimate[0] = bp->cmd_rsp_virt->smt_mib_get.port_ler_estimate[0];
	bp->stats.port_ler_estimate[1] = bp->cmd_rsp_virt->smt_mib_get.port_ler_estimate[1];
	bp->stats.port_ler_cutoff[0] = bp->cmd_rsp_virt->smt_mib_get.port_ler_cutoff[0];
	bp->stats.port_ler_cutoff[1] = bp->cmd_rsp_virt->smt_mib_get.port_ler_cutoff[1];
	bp->stats.port_ler_alarm[0] = bp->cmd_rsp_virt->smt_mib_get.port_ler_alarm[0];
	bp->stats.port_ler_alarm[1] = bp->cmd_rsp_virt->smt_mib_get.port_ler_alarm[1];
	bp->stats.port_connect_state[0] = bp->cmd_rsp_virt->smt_mib_get.port_connect_state[0];
	bp->stats.port_connect_state[1] = bp->cmd_rsp_virt->smt_mib_get.port_connect_state[1];
	bp->stats.port_pcm_state[0] = bp->cmd_rsp_virt->smt_mib_get.port_pcm_state[0];
	bp->stats.port_pcm_state[1] = bp->cmd_rsp_virt->smt_mib_get.port_pcm_state[1];
	bp->stats.port_pc_withhold[0] = bp->cmd_rsp_virt->smt_mib_get.port_pc_withhold[0];
	bp->stats.port_pc_withhold[1] = bp->cmd_rsp_virt->smt_mib_get.port_pc_withhold[1];
	bp->stats.port_ler_flag[0] = bp->cmd_rsp_virt->smt_mib_get.port_ler_flag[0];
	bp->stats.port_ler_flag[1] = bp->cmd_rsp_virt->smt_mib_get.port_ler_flag[1];
	bp->stats.port_hardware_present[0] = bp->cmd_rsp_virt->smt_mib_get.port_hardware_present[0];
	bp->stats.port_hardware_present[1] = bp->cmd_rsp_virt->smt_mib_get.port_hardware_present[1];


	/* Fill the bp->stats structure with the FDDI counter values */

	bp->stats.mac_frame_cts = bp->cmd_rsp_virt->cntrs_get.cntrs.frame_cnt.ls;
	bp->stats.mac_copied_cts = bp->cmd_rsp_virt->cntrs_get.cntrs.copied_cnt.ls;
	bp->stats.mac_transmit_cts = bp->cmd_rsp_virt->cntrs_get.cntrs.transmit_cnt.ls;
	bp->stats.mac_error_cts = bp->cmd_rsp_virt->cntrs_get.cntrs.error_cnt.ls;
	bp->stats.mac_lost_cts = bp->cmd_rsp_virt->cntrs_get.cntrs.lost_cnt.ls;
	bp->stats.port_lct_fail_cts[0] = bp->cmd_rsp_virt->cntrs_get.cntrs.lct_rejects[0].ls;
	bp->stats.port_lct_fail_cts[1] = bp->cmd_rsp_virt->cntrs_get.cntrs.lct_rejects[1].ls;
	bp->stats.port_lem_reject_cts[0] = bp->cmd_rsp_virt->cntrs_get.cntrs.lem_rejects[0].ls;
	bp->stats.port_lem_reject_cts[1] = bp->cmd_rsp_virt->cntrs_get.cntrs.lem_rejects[1].ls;
	bp->stats.port_lem_cts[0] = bp->cmd_rsp_virt->cntrs_get.cntrs.link_errors[0].ls;
	bp->stats.port_lem_cts[1] = bp->cmd_rsp_virt->cntrs_get.cntrs.link_errors[1].ls;

#endif
	return (struct net_device_stats *)&bp->os.MacStat;
}