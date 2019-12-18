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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_2__ {scalar_t__ num_present_cpu; } ;
struct lpfc_hba {scalar_t__ sli_rev; int hba_flag; int cfg_enable_fc4_type; int cfg_auto_imax; scalar_t__ cfg_hdw_queue; scalar_t__ cfg_irq_chann; long cfg_soft_wwnn; long cfg_soft_wwpn; int cfg_enable_dss; TYPE_1__ sli4_hba; scalar_t__ cfg_enable_pbde; scalar_t__ cfg_fcp_imax; scalar_t__ cfg_xri_rebalancing; scalar_t__ cfg_enable_bbcr; scalar_t__ cfg_nvmet_mrq; scalar_t__ nvmet_support; int /*<<< orphan*/  sli3_options; scalar_t__ cfg_enable_bg; scalar_t__ cfg_poll; scalar_t__ cfg_oas_priority; scalar_t__ cfg_oas_flags; scalar_t__ cfg_oas_lun_status; scalar_t__ cfg_oas_lun_state; int /*<<< orphan*/  cfg_oas_vpt_wwpn; int /*<<< orphan*/  cfg_oas_tgt_wwpn; scalar_t__ cfg_EnableXLane; } ;

/* Variables and functions */
 int HBA_FCOE_MODE ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  LOG_INIT ; 
 int LPFC_ENABLE_FCP ; 
 int /*<<< orphan*/  LPFC_SLI3_BG_ENABLED ; 
 scalar_t__ LPFC_SLI_REV4 ; 
 int /*<<< orphan*/  lpfc_EnableXLane ; 
 int /*<<< orphan*/  lpfc_EnableXLane_init (struct lpfc_hba*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_XLanePriority ; 
 int /*<<< orphan*/  lpfc_XLanePriority_init (struct lpfc_hba*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_ack0 ; 
 int /*<<< orphan*/  lpfc_ack0_init (struct lpfc_hba*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_aer_support ; 
 int /*<<< orphan*/  lpfc_aer_support_init (struct lpfc_hba*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_cq_max_proc_limit ; 
 int /*<<< orphan*/  lpfc_cq_max_proc_limit_init (struct lpfc_hba*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_cq_poll_threshold ; 
 int /*<<< orphan*/  lpfc_cq_poll_threshold_init (struct lpfc_hba*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_cr_count ; 
 int /*<<< orphan*/  lpfc_cr_count_init (struct lpfc_hba*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_cr_delay ; 
 int /*<<< orphan*/  lpfc_cr_delay_init (struct lpfc_hba*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_delay_discovery ; 
 int /*<<< orphan*/  lpfc_delay_discovery_init (struct lpfc_hba*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_enable_SmartSAN ; 
 int /*<<< orphan*/  lpfc_enable_SmartSAN_init (struct lpfc_hba*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_enable_bbcr ; 
 int /*<<< orphan*/  lpfc_enable_bbcr_init (struct lpfc_hba*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_enable_bg ; 
 int /*<<< orphan*/  lpfc_enable_bg_init (struct lpfc_hba*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_enable_dpp ; 
 int /*<<< orphan*/  lpfc_enable_dpp_init (struct lpfc_hba*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_enable_fc4_type ; 
 int /*<<< orphan*/  lpfc_enable_fc4_type_init (struct lpfc_hba*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_enable_hba_heartbeat ; 
 int /*<<< orphan*/  lpfc_enable_hba_heartbeat_init (struct lpfc_hba*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_enable_hba_reset ; 
 int /*<<< orphan*/  lpfc_enable_hba_reset_init (struct lpfc_hba*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_enable_mds_diags ; 
 int /*<<< orphan*/  lpfc_enable_mds_diags_init (struct lpfc_hba*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_enable_npiv ; 
 int /*<<< orphan*/  lpfc_enable_npiv_init (struct lpfc_hba*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_enable_rrq ; 
 int /*<<< orphan*/  lpfc_enable_rrq_init (struct lpfc_hba*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_fcf_failover_policy ; 
 int /*<<< orphan*/  lpfc_fcf_failover_policy_init (struct lpfc_hba*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_fcp2_no_tgt_reset ; 
 int /*<<< orphan*/  lpfc_fcp2_no_tgt_reset_init (struct lpfc_hba*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_fcp_cpu_map ; 
 int /*<<< orphan*/  lpfc_fcp_cpu_map_init (struct lpfc_hba*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_fcp_imax ; 
 int /*<<< orphan*/  lpfc_fcp_imax_init (struct lpfc_hba*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_fcp_io_sched ; 
 int /*<<< orphan*/  lpfc_fcp_io_sched_init (struct lpfc_hba*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_fcp_mq_threshold ; 
 int /*<<< orphan*/  lpfc_fcp_mq_threshold_init (struct lpfc_hba*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_fdmi_on ; 
 int /*<<< orphan*/  lpfc_fdmi_on_init (struct lpfc_hba*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_force_rscn ; 
 int /*<<< orphan*/  lpfc_force_rscn_init (struct lpfc_hba*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_get_hba_function_mode (struct lpfc_hba*) ; 
 int /*<<< orphan*/  lpfc_hba_log_verbose_init (struct lpfc_hba*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_hba_queue_depth ; 
 int /*<<< orphan*/  lpfc_hba_queue_depth_init (struct lpfc_hba*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_hdw_queue ; 
 int /*<<< orphan*/  lpfc_hdw_queue_init (struct lpfc_hba*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_iocb_cnt ; 
 int /*<<< orphan*/  lpfc_iocb_cnt_init (struct lpfc_hba*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_irq_chann ; 
 int /*<<< orphan*/  lpfc_irq_chann_init (struct lpfc_hba*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_link_speed ; 
 int /*<<< orphan*/  lpfc_link_speed_init (struct lpfc_hba*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_log_verbose ; 
 int /*<<< orphan*/  lpfc_multi_ring_rctl ; 
 int /*<<< orphan*/  lpfc_multi_ring_rctl_init (struct lpfc_hba*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_multi_ring_support ; 
 int /*<<< orphan*/  lpfc_multi_ring_support_init (struct lpfc_hba*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_multi_ring_type ; 
 int /*<<< orphan*/  lpfc_multi_ring_type_init (struct lpfc_hba*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_ns_query ; 
 int /*<<< orphan*/  lpfc_ns_query_init (struct lpfc_hba*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_nvme_embed_cmd ; 
 int /*<<< orphan*/  lpfc_nvme_embed_cmd_init (struct lpfc_hba*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_nvme_enable_fb ; 
 int /*<<< orphan*/  lpfc_nvme_enable_fb_init (struct lpfc_hba*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_nvme_oas ; 
 int /*<<< orphan*/  lpfc_nvme_oas_init (struct lpfc_hba*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_nvmet_fb_size ; 
 int /*<<< orphan*/  lpfc_nvmet_fb_size_init (struct lpfc_hba*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_nvmet_mrq ; 
 int /*<<< orphan*/  lpfc_nvmet_mrq_init (struct lpfc_hba*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_nvmet_mrq_post ; 
 int /*<<< orphan*/  lpfc_nvmet_mrq_post_init (struct lpfc_hba*,int /*<<< orphan*/ ) ; 
 scalar_t__ lpfc_poll ; 
 int /*<<< orphan*/  lpfc_poll_tmo ; 
 int /*<<< orphan*/  lpfc_poll_tmo_init (struct lpfc_hba*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_printf_log (struct lpfc_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  lpfc_prot_guard ; 
 int /*<<< orphan*/  lpfc_prot_guard_init (struct lpfc_hba*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_prot_mask ; 
 int /*<<< orphan*/  lpfc_prot_mask_init (struct lpfc_hba*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_ras_fwlog_buffsize ; 
 int /*<<< orphan*/  lpfc_ras_fwlog_buffsize_init (struct lpfc_hba*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_ras_fwlog_func ; 
 int /*<<< orphan*/  lpfc_ras_fwlog_func_init (struct lpfc_hba*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_ras_fwlog_level ; 
 int /*<<< orphan*/  lpfc_ras_fwlog_level_init (struct lpfc_hba*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_req_fw_upgrade ; 
 int /*<<< orphan*/  lpfc_request_firmware_upgrade_init (struct lpfc_hba*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_sg_seg_cnt ; 
 int /*<<< orphan*/  lpfc_sg_seg_cnt_init (struct lpfc_hba*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_sli_mode ; 
 int /*<<< orphan*/  lpfc_sli_mode_init (struct lpfc_hba*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_sriov_nr_virtfn ; 
 int /*<<< orphan*/  lpfc_sriov_nr_virtfn_init (struct lpfc_hba*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_suppress_link_up ; 
 int /*<<< orphan*/  lpfc_suppress_link_up_init (struct lpfc_hba*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_suppress_rsp ; 
 int /*<<< orphan*/  lpfc_suppress_rsp_init (struct lpfc_hba*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_task_mgmt_tmo ; 
 int /*<<< orphan*/  lpfc_task_mgmt_tmo_init (struct lpfc_hba*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_topology ; 
 int /*<<< orphan*/  lpfc_topology_init (struct lpfc_hba*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_use_msi ; 
 int /*<<< orphan*/  lpfc_use_msi_init (struct lpfc_hba*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_xri_rebalancing ; 
 int /*<<< orphan*/  lpfc_xri_rebalancing_init (struct lpfc_hba*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void
lpfc_get_cfgparam(struct lpfc_hba *phba)
{
	lpfc_fcp_io_sched_init(phba, lpfc_fcp_io_sched);
	lpfc_ns_query_init(phba, lpfc_ns_query);
	lpfc_fcp2_no_tgt_reset_init(phba, lpfc_fcp2_no_tgt_reset);
	lpfc_cr_delay_init(phba, lpfc_cr_delay);
	lpfc_cr_count_init(phba, lpfc_cr_count);
	lpfc_multi_ring_support_init(phba, lpfc_multi_ring_support);
	lpfc_multi_ring_rctl_init(phba, lpfc_multi_ring_rctl);
	lpfc_multi_ring_type_init(phba, lpfc_multi_ring_type);
	lpfc_ack0_init(phba, lpfc_ack0);
	lpfc_xri_rebalancing_init(phba, lpfc_xri_rebalancing);
	lpfc_topology_init(phba, lpfc_topology);
	lpfc_link_speed_init(phba, lpfc_link_speed);
	lpfc_poll_tmo_init(phba, lpfc_poll_tmo);
	lpfc_task_mgmt_tmo_init(phba, lpfc_task_mgmt_tmo);
	lpfc_enable_npiv_init(phba, lpfc_enable_npiv);
	lpfc_fcf_failover_policy_init(phba, lpfc_fcf_failover_policy);
	lpfc_enable_rrq_init(phba, lpfc_enable_rrq);
	lpfc_fdmi_on_init(phba, lpfc_fdmi_on);
	lpfc_enable_SmartSAN_init(phba, lpfc_enable_SmartSAN);
	lpfc_use_msi_init(phba, lpfc_use_msi);
	lpfc_nvme_oas_init(phba, lpfc_nvme_oas);
	lpfc_nvme_embed_cmd_init(phba, lpfc_nvme_embed_cmd);
	lpfc_fcp_imax_init(phba, lpfc_fcp_imax);
	lpfc_force_rscn_init(phba, lpfc_force_rscn);
	lpfc_cq_poll_threshold_init(phba, lpfc_cq_poll_threshold);
	lpfc_cq_max_proc_limit_init(phba, lpfc_cq_max_proc_limit);
	lpfc_fcp_cpu_map_init(phba, lpfc_fcp_cpu_map);
	lpfc_enable_hba_reset_init(phba, lpfc_enable_hba_reset);
	lpfc_enable_hba_heartbeat_init(phba, lpfc_enable_hba_heartbeat);

	lpfc_EnableXLane_init(phba, lpfc_EnableXLane);
	if (phba->sli_rev != LPFC_SLI_REV4)
		phba->cfg_EnableXLane = 0;
	lpfc_XLanePriority_init(phba, lpfc_XLanePriority);

	memset(phba->cfg_oas_tgt_wwpn, 0, (8 * sizeof(uint8_t)));
	memset(phba->cfg_oas_vpt_wwpn, 0, (8 * sizeof(uint8_t)));
	phba->cfg_oas_lun_state = 0;
	phba->cfg_oas_lun_status = 0;
	phba->cfg_oas_flags = 0;
	phba->cfg_oas_priority = 0;
	lpfc_enable_bg_init(phba, lpfc_enable_bg);
	lpfc_prot_mask_init(phba, lpfc_prot_mask);
	lpfc_prot_guard_init(phba, lpfc_prot_guard);
	if (phba->sli_rev == LPFC_SLI_REV4)
		phba->cfg_poll = 0;
	else
		phba->cfg_poll = lpfc_poll;

	/* Get the function mode */
	lpfc_get_hba_function_mode(phba);

	/* BlockGuard allowed for FC only. */
	if (phba->cfg_enable_bg && phba->hba_flag & HBA_FCOE_MODE) {
		lpfc_printf_log(phba, KERN_INFO, LOG_INIT,
				"0581 BlockGuard feature not supported\n");
		/* If set, clear the BlockGuard support param */
		phba->cfg_enable_bg = 0;
	} else if (phba->cfg_enable_bg) {
		phba->sli3_options |= LPFC_SLI3_BG_ENABLED;
	}

	lpfc_suppress_rsp_init(phba, lpfc_suppress_rsp);

	lpfc_enable_fc4_type_init(phba, lpfc_enable_fc4_type);
	lpfc_nvmet_mrq_init(phba, lpfc_nvmet_mrq);
	lpfc_nvmet_mrq_post_init(phba, lpfc_nvmet_mrq_post);

	/* Initialize first burst. Target vs Initiator are different. */
	lpfc_nvme_enable_fb_init(phba, lpfc_nvme_enable_fb);
	lpfc_nvmet_fb_size_init(phba, lpfc_nvmet_fb_size);
	lpfc_fcp_mq_threshold_init(phba, lpfc_fcp_mq_threshold);
	lpfc_hdw_queue_init(phba, lpfc_hdw_queue);
	lpfc_irq_chann_init(phba, lpfc_irq_chann);
	lpfc_enable_bbcr_init(phba, lpfc_enable_bbcr);
	lpfc_enable_dpp_init(phba, lpfc_enable_dpp);

	if (phba->sli_rev != LPFC_SLI_REV4) {
		/* NVME only supported on SLI4 */
		phba->nvmet_support = 0;
		phba->cfg_nvmet_mrq = 0;
		phba->cfg_enable_fc4_type = LPFC_ENABLE_FCP;
		phba->cfg_enable_bbcr = 0;
		phba->cfg_xri_rebalancing = 0;
	} else {
		/* We MUST have FCP support */
		if (!(phba->cfg_enable_fc4_type & LPFC_ENABLE_FCP))
			phba->cfg_enable_fc4_type |= LPFC_ENABLE_FCP;
	}

	phba->cfg_auto_imax = (phba->cfg_fcp_imax) ? 0 : 1;

	phba->cfg_enable_pbde = 0;

	/* A value of 0 means use the number of CPUs found in the system */
	if (phba->cfg_hdw_queue == 0)
		phba->cfg_hdw_queue = phba->sli4_hba.num_present_cpu;
	if (phba->cfg_irq_chann == 0)
		phba->cfg_irq_chann = phba->sli4_hba.num_present_cpu;
	if (phba->cfg_irq_chann > phba->cfg_hdw_queue)
		phba->cfg_irq_chann = phba->cfg_hdw_queue;

	phba->cfg_soft_wwnn = 0L;
	phba->cfg_soft_wwpn = 0L;
	lpfc_sg_seg_cnt_init(phba, lpfc_sg_seg_cnt);
	lpfc_hba_queue_depth_init(phba, lpfc_hba_queue_depth);
	lpfc_hba_log_verbose_init(phba, lpfc_log_verbose);
	lpfc_aer_support_init(phba, lpfc_aer_support);
	lpfc_sriov_nr_virtfn_init(phba, lpfc_sriov_nr_virtfn);
	lpfc_request_firmware_upgrade_init(phba, lpfc_req_fw_upgrade);
	lpfc_suppress_link_up_init(phba, lpfc_suppress_link_up);
	lpfc_iocb_cnt_init(phba, lpfc_iocb_cnt);
	lpfc_delay_discovery_init(phba, lpfc_delay_discovery);
	lpfc_sli_mode_init(phba, lpfc_sli_mode);
	phba->cfg_enable_dss = 1;
	lpfc_enable_mds_diags_init(phba, lpfc_enable_mds_diags);
	lpfc_ras_fwlog_buffsize_init(phba, lpfc_ras_fwlog_buffsize);
	lpfc_ras_fwlog_level_init(phba, lpfc_ras_fwlog_level);
	lpfc_ras_fwlog_func_init(phba, lpfc_ras_fwlog_func);

	return;
}