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
struct wl1271 {int dummy; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFS_ADD (int /*<<< orphan*/ ,struct dentry*) ; 
 int /*<<< orphan*/  DEBUGFS_FWSTATS_ADD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* KBUILD_MODNAME ; 
 int /*<<< orphan*/  accum_arp_pend_requests ; 
 int /*<<< orphan*/  adc_source_unexpected ; 
 int /*<<< orphan*/  aggr_size ; 
 int /*<<< orphan*/  ap_sleep_active_conf ; 
 int /*<<< orphan*/  ap_sleep_counter ; 
 int /*<<< orphan*/  ap_sleep_user_conf ; 
 int /*<<< orphan*/  arp_filter ; 
 int /*<<< orphan*/  bar_retry ; 
 int /*<<< orphan*/  beacon_filter ; 
 int /*<<< orphan*/  burst_mismatch ; 
 int /*<<< orphan*/  calib ; 
 int /*<<< orphan*/  calib_count ; 
 int /*<<< orphan*/  clear_fw_stats ; 
 int /*<<< orphan*/  conf ; 
 int /*<<< orphan*/  connection_out_of_sync ; 
 int /*<<< orphan*/  cont_miss_bcns_spread ; 
 int /*<<< orphan*/  data_filter ; 
 struct dentry* debugfs_create_dir (char*,struct dentry*) ; 
 int /*<<< orphan*/  dec_packet_in ; 
 int /*<<< orphan*/  dec_packet_in_fifo_full ; 
 int /*<<< orphan*/  dec_packet_out ; 
 int /*<<< orphan*/  decrypt_key_not_found ; 
 int /*<<< orphan*/  defrag_called ; 
 int /*<<< orphan*/  defrag_decrypt_failed ; 
 int /*<<< orphan*/  defrag_in_process_called ; 
 int /*<<< orphan*/  defrag_init_called ; 
 int /*<<< orphan*/  defrag_need_decrypt ; 
 int /*<<< orphan*/  defrag_need_defrag ; 
 int /*<<< orphan*/  defrag_tkip_called ; 
 int /*<<< orphan*/  defrag_to_rx_xfer_swi ; 
 int /*<<< orphan*/  dfs ; 
 int /*<<< orphan*/  diversity ; 
 int /*<<< orphan*/  dup_filter ; 
 int /*<<< orphan*/  dynamic_fw_traces ; 
 int /*<<< orphan*/  elp_while_nvic_pending ; 
 int /*<<< orphan*/  elp_while_rx_exch ; 
 int /*<<< orphan*/  elp_while_tx ; 
 int /*<<< orphan*/  elp_while_tx_exch ; 
 int /*<<< orphan*/  enc_rx_stat_fifo_int ; 
 int /*<<< orphan*/  enc_tx_stat_fifo_int ; 
 int /*<<< orphan*/  error ; 
 int /*<<< orphan*/  error_frame_ctrl ; 
 int /*<<< orphan*/  error_frame_during_protection ; 
 int /*<<< orphan*/  error_frame_non_ctrl ; 
 int /*<<< orphan*/  fail_count ; 
 int /*<<< orphan*/  false_irq ; 
 int /*<<< orphan*/  frag_bad_mblk_num ; 
 int /*<<< orphan*/  frag_cache_hit ; 
 int /*<<< orphan*/  frag_cache_miss ; 
 int /*<<< orphan*/  frag_called ; 
 int /*<<< orphan*/  frag_failed ; 
 int /*<<< orphan*/  frag_in_process_called ; 
 int /*<<< orphan*/  frag_init_called ; 
 int /*<<< orphan*/  frag_key_not_found ; 
 int /*<<< orphan*/  frag_mpdu_alloc_failed ; 
 int /*<<< orphan*/  frag_need_fragmentation ; 
 int /*<<< orphan*/  frag_tkip_called ; 
 int /*<<< orphan*/  hs_tx_stat_fifo_int ; 
 int /*<<< orphan*/  ibss_filter ; 
 int /*<<< orphan*/  irq_thr_high ; 
 int /*<<< orphan*/  irq_thr_low ; 
 int /*<<< orphan*/  irqs ; 
 int /*<<< orphan*/  isr ; 
 int /*<<< orphan*/  max_arp_queue_dep ; 
 int /*<<< orphan*/  mc_filter ; 
 int /*<<< orphan*/  missing_bcns_cnt ; 
 int /*<<< orphan*/  null_frame_cts_start ; 
 int /*<<< orphan*/  null_frame_tx_start ; 
 int /*<<< orphan*/  num_frame_cts_nul_flid ; 
 int /*<<< orphan*/  num_of_packets_per_ant ; 
 int /*<<< orphan*/  num_of_radar_detections ; 
 int /*<<< orphan*/  pipeline ; 
 int /*<<< orphan*/  pipeline_fifo_full ; 
 int /*<<< orphan*/  post_proc_swi ; 
 int /*<<< orphan*/  pre_proc_swi ; 
 int /*<<< orphan*/  pre_to_defrag_swi ; 
 int /*<<< orphan*/  protection_filter ; 
 int /*<<< orphan*/  pwr ; 
 int /*<<< orphan*/  radar_debug_mode ; 
 int /*<<< orphan*/  radar_detection ; 
 int /*<<< orphan*/  rcvd_awake_bcns_cnt ; 
 int /*<<< orphan*/  rcvd_bcns_cnt ; 
 int /*<<< orphan*/  roaming ; 
 int /*<<< orphan*/  rssi_level ; 
 int /*<<< orphan*/  rx ; 
 int /*<<< orphan*/  rx_beacon_early_term ; 
 int /*<<< orphan*/  rx_cmplt ; 
 int /*<<< orphan*/  rx_cmplt_db_overflow_cnt ; 
 int /*<<< orphan*/  rx_cmplt_task ; 
 int /*<<< orphan*/  rx_complete_stat_fifo_int ; 
 int /*<<< orphan*/  rx_defrag ; 
 int /*<<< orphan*/  rx_defrag_end ; 
 int /*<<< orphan*/  rx_done ; 
 int /*<<< orphan*/  rx_dropped_frame ; 
 int /*<<< orphan*/  rx_excessive_frame_len ; 
 int /*<<< orphan*/  rx_filter ; 
 int /*<<< orphan*/  rx_frames_per_rates ; 
 int /*<<< orphan*/  rx_hdr_overflow ; 
 int /*<<< orphan*/  rx_out_of_mpdu_nodes ; 
 int /*<<< orphan*/  rx_phy_hdr ; 
 int /*<<< orphan*/  rx_pre_complt ; 
 int /*<<< orphan*/  rx_rate ; 
 int /*<<< orphan*/  rx_rts_timeout ; 
 int /*<<< orphan*/  rx_size ; 
 int /*<<< orphan*/  rx_timeout ; 
 int /*<<< orphan*/  rx_timeout_wa ; 
 int /*<<< orphan*/  rx_tkip_replays ; 
 int /*<<< orphan*/  rx_xfr ; 
 int /*<<< orphan*/  sec_frag_swi ; 
 int /*<<< orphan*/  sleep_cycle_avg ; 
 int /*<<< orphan*/  sleep_percent ; 
 int /*<<< orphan*/  sleep_time_avg ; 
 int /*<<< orphan*/  sleep_time_count ; 
 int /*<<< orphan*/  tbc_exch_mismatch ; 
 int /*<<< orphan*/  thermal ; 
 int /*<<< orphan*/  total_num_of_toggles ; 
 int /*<<< orphan*/  tx ; 
 int /*<<< orphan*/  tx_abort_failure ; 
 int /*<<< orphan*/  tx_agg_len ; 
 int /*<<< orphan*/  tx_agg_rate ; 
 int /*<<< orphan*/  tx_burst_programmed ; 
 int /*<<< orphan*/  tx_cfe1 ; 
 int /*<<< orphan*/  tx_cfe2 ; 
 int /*<<< orphan*/  tx_cmplt ; 
 int /*<<< orphan*/  tx_data_prepared ; 
 int /*<<< orphan*/  tx_data_programmed ; 
 int /*<<< orphan*/  tx_done_data ; 
 int /*<<< orphan*/  tx_done_int_template ; 
 int /*<<< orphan*/  tx_done_template ; 
 int /*<<< orphan*/  tx_exch ; 
 int /*<<< orphan*/  tx_exch_expiry ; 
 int /*<<< orphan*/  tx_exch_pending ; 
 int /*<<< orphan*/  tx_prepared_descs ; 
 int /*<<< orphan*/  tx_resume ; 
 int /*<<< orphan*/  tx_resume_failure ; 
 int /*<<< orphan*/  tx_retry_data ; 
 int /*<<< orphan*/  tx_retry_per_rate ; 
 int /*<<< orphan*/  tx_retry_template ; 
 int /*<<< orphan*/  tx_start_data ; 
 int /*<<< orphan*/  tx_start_fw_gen ; 
 int /*<<< orphan*/  tx_start_int_templates ; 
 int /*<<< orphan*/  tx_start_null_frame ; 
 int /*<<< orphan*/  tx_start_templates ; 
 int /*<<< orphan*/  tx_starts ; 
 int /*<<< orphan*/  tx_stop ; 
 int /*<<< orphan*/  tx_template_prepared ; 
 int /*<<< orphan*/  tx_template_programmed ; 

int wl18xx_debugfs_add_files(struct wl1271 *wl,
			     struct dentry *rootdir)
{
	struct dentry *stats, *moddir;

	moddir = debugfs_create_dir(KBUILD_MODNAME, rootdir);
	stats = debugfs_create_dir("fw_stats", moddir);

	DEBUGFS_ADD(clear_fw_stats, stats);

	DEBUGFS_FWSTATS_ADD(error, error_frame_non_ctrl);
	DEBUGFS_FWSTATS_ADD(error, error_frame_ctrl);
	DEBUGFS_FWSTATS_ADD(error, error_frame_during_protection);
	DEBUGFS_FWSTATS_ADD(error, null_frame_tx_start);
	DEBUGFS_FWSTATS_ADD(error, null_frame_cts_start);
	DEBUGFS_FWSTATS_ADD(error, bar_retry);
	DEBUGFS_FWSTATS_ADD(error, num_frame_cts_nul_flid);
	DEBUGFS_FWSTATS_ADD(error, tx_abort_failure);
	DEBUGFS_FWSTATS_ADD(error, tx_resume_failure);
	DEBUGFS_FWSTATS_ADD(error, rx_cmplt_db_overflow_cnt);
	DEBUGFS_FWSTATS_ADD(error, elp_while_rx_exch);
	DEBUGFS_FWSTATS_ADD(error, elp_while_tx_exch);
	DEBUGFS_FWSTATS_ADD(error, elp_while_tx);
	DEBUGFS_FWSTATS_ADD(error, elp_while_nvic_pending);
	DEBUGFS_FWSTATS_ADD(error, rx_excessive_frame_len);
	DEBUGFS_FWSTATS_ADD(error, burst_mismatch);
	DEBUGFS_FWSTATS_ADD(error, tbc_exch_mismatch);

	DEBUGFS_FWSTATS_ADD(tx, tx_prepared_descs);
	DEBUGFS_FWSTATS_ADD(tx, tx_cmplt);
	DEBUGFS_FWSTATS_ADD(tx, tx_template_prepared);
	DEBUGFS_FWSTATS_ADD(tx, tx_data_prepared);
	DEBUGFS_FWSTATS_ADD(tx, tx_template_programmed);
	DEBUGFS_FWSTATS_ADD(tx, tx_data_programmed);
	DEBUGFS_FWSTATS_ADD(tx, tx_burst_programmed);
	DEBUGFS_FWSTATS_ADD(tx, tx_starts);
	DEBUGFS_FWSTATS_ADD(tx, tx_stop);
	DEBUGFS_FWSTATS_ADD(tx, tx_start_templates);
	DEBUGFS_FWSTATS_ADD(tx, tx_start_int_templates);
	DEBUGFS_FWSTATS_ADD(tx, tx_start_fw_gen);
	DEBUGFS_FWSTATS_ADD(tx, tx_start_data);
	DEBUGFS_FWSTATS_ADD(tx, tx_start_null_frame);
	DEBUGFS_FWSTATS_ADD(tx, tx_exch);
	DEBUGFS_FWSTATS_ADD(tx, tx_retry_template);
	DEBUGFS_FWSTATS_ADD(tx, tx_retry_data);
	DEBUGFS_FWSTATS_ADD(tx, tx_retry_per_rate);
	DEBUGFS_FWSTATS_ADD(tx, tx_exch_pending);
	DEBUGFS_FWSTATS_ADD(tx, tx_exch_expiry);
	DEBUGFS_FWSTATS_ADD(tx, tx_done_template);
	DEBUGFS_FWSTATS_ADD(tx, tx_done_data);
	DEBUGFS_FWSTATS_ADD(tx, tx_done_int_template);
	DEBUGFS_FWSTATS_ADD(tx, tx_cfe1);
	DEBUGFS_FWSTATS_ADD(tx, tx_cfe2);
	DEBUGFS_FWSTATS_ADD(tx, frag_called);
	DEBUGFS_FWSTATS_ADD(tx, frag_mpdu_alloc_failed);
	DEBUGFS_FWSTATS_ADD(tx, frag_init_called);
	DEBUGFS_FWSTATS_ADD(tx, frag_in_process_called);
	DEBUGFS_FWSTATS_ADD(tx, frag_tkip_called);
	DEBUGFS_FWSTATS_ADD(tx, frag_key_not_found);
	DEBUGFS_FWSTATS_ADD(tx, frag_need_fragmentation);
	DEBUGFS_FWSTATS_ADD(tx, frag_bad_mblk_num);
	DEBUGFS_FWSTATS_ADD(tx, frag_failed);
	DEBUGFS_FWSTATS_ADD(tx, frag_cache_hit);
	DEBUGFS_FWSTATS_ADD(tx, frag_cache_miss);

	DEBUGFS_FWSTATS_ADD(rx, rx_beacon_early_term);
	DEBUGFS_FWSTATS_ADD(rx, rx_out_of_mpdu_nodes);
	DEBUGFS_FWSTATS_ADD(rx, rx_hdr_overflow);
	DEBUGFS_FWSTATS_ADD(rx, rx_dropped_frame);
	DEBUGFS_FWSTATS_ADD(rx, rx_done);
	DEBUGFS_FWSTATS_ADD(rx, rx_defrag);
	DEBUGFS_FWSTATS_ADD(rx, rx_defrag_end);
	DEBUGFS_FWSTATS_ADD(rx, rx_cmplt);
	DEBUGFS_FWSTATS_ADD(rx, rx_pre_complt);
	DEBUGFS_FWSTATS_ADD(rx, rx_cmplt_task);
	DEBUGFS_FWSTATS_ADD(rx, rx_phy_hdr);
	DEBUGFS_FWSTATS_ADD(rx, rx_timeout);
	DEBUGFS_FWSTATS_ADD(rx, rx_rts_timeout);
	DEBUGFS_FWSTATS_ADD(rx, rx_timeout_wa);
	DEBUGFS_FWSTATS_ADD(rx, defrag_called);
	DEBUGFS_FWSTATS_ADD(rx, defrag_init_called);
	DEBUGFS_FWSTATS_ADD(rx, defrag_in_process_called);
	DEBUGFS_FWSTATS_ADD(rx, defrag_tkip_called);
	DEBUGFS_FWSTATS_ADD(rx, defrag_need_defrag);
	DEBUGFS_FWSTATS_ADD(rx, defrag_decrypt_failed);
	DEBUGFS_FWSTATS_ADD(rx, decrypt_key_not_found);
	DEBUGFS_FWSTATS_ADD(rx, defrag_need_decrypt);
	DEBUGFS_FWSTATS_ADD(rx, rx_tkip_replays);
	DEBUGFS_FWSTATS_ADD(rx, rx_xfr);

	DEBUGFS_FWSTATS_ADD(isr, irqs);

	DEBUGFS_FWSTATS_ADD(pwr, missing_bcns_cnt);
	DEBUGFS_FWSTATS_ADD(pwr, rcvd_bcns_cnt);
	DEBUGFS_FWSTATS_ADD(pwr, connection_out_of_sync);
	DEBUGFS_FWSTATS_ADD(pwr, cont_miss_bcns_spread);
	DEBUGFS_FWSTATS_ADD(pwr, rcvd_awake_bcns_cnt);
	DEBUGFS_FWSTATS_ADD(pwr, sleep_time_count);
	DEBUGFS_FWSTATS_ADD(pwr, sleep_time_avg);
	DEBUGFS_FWSTATS_ADD(pwr, sleep_cycle_avg);
	DEBUGFS_FWSTATS_ADD(pwr, sleep_percent);
	DEBUGFS_FWSTATS_ADD(pwr, ap_sleep_active_conf);
	DEBUGFS_FWSTATS_ADD(pwr, ap_sleep_user_conf);
	DEBUGFS_FWSTATS_ADD(pwr, ap_sleep_counter);

	DEBUGFS_FWSTATS_ADD(rx_filter, beacon_filter);
	DEBUGFS_FWSTATS_ADD(rx_filter, arp_filter);
	DEBUGFS_FWSTATS_ADD(rx_filter, mc_filter);
	DEBUGFS_FWSTATS_ADD(rx_filter, dup_filter);
	DEBUGFS_FWSTATS_ADD(rx_filter, data_filter);
	DEBUGFS_FWSTATS_ADD(rx_filter, ibss_filter);
	DEBUGFS_FWSTATS_ADD(rx_filter, protection_filter);
	DEBUGFS_FWSTATS_ADD(rx_filter, accum_arp_pend_requests);
	DEBUGFS_FWSTATS_ADD(rx_filter, max_arp_queue_dep);

	DEBUGFS_FWSTATS_ADD(rx_rate, rx_frames_per_rates);

	DEBUGFS_FWSTATS_ADD(aggr_size, tx_agg_rate);
	DEBUGFS_FWSTATS_ADD(aggr_size, tx_agg_len);
	DEBUGFS_FWSTATS_ADD(aggr_size, rx_size);

	DEBUGFS_FWSTATS_ADD(pipeline, hs_tx_stat_fifo_int);
	DEBUGFS_FWSTATS_ADD(pipeline, enc_tx_stat_fifo_int);
	DEBUGFS_FWSTATS_ADD(pipeline, enc_rx_stat_fifo_int);
	DEBUGFS_FWSTATS_ADD(pipeline, rx_complete_stat_fifo_int);
	DEBUGFS_FWSTATS_ADD(pipeline, pre_proc_swi);
	DEBUGFS_FWSTATS_ADD(pipeline, post_proc_swi);
	DEBUGFS_FWSTATS_ADD(pipeline, sec_frag_swi);
	DEBUGFS_FWSTATS_ADD(pipeline, pre_to_defrag_swi);
	DEBUGFS_FWSTATS_ADD(pipeline, defrag_to_rx_xfer_swi);
	DEBUGFS_FWSTATS_ADD(pipeline, dec_packet_in);
	DEBUGFS_FWSTATS_ADD(pipeline, dec_packet_in_fifo_full);
	DEBUGFS_FWSTATS_ADD(pipeline, dec_packet_out);
	DEBUGFS_FWSTATS_ADD(pipeline, pipeline_fifo_full);

	DEBUGFS_FWSTATS_ADD(diversity, num_of_packets_per_ant);
	DEBUGFS_FWSTATS_ADD(diversity, total_num_of_toggles);

	DEBUGFS_FWSTATS_ADD(thermal, irq_thr_low);
	DEBUGFS_FWSTATS_ADD(thermal, irq_thr_high);
	DEBUGFS_FWSTATS_ADD(thermal, tx_stop);
	DEBUGFS_FWSTATS_ADD(thermal, tx_resume);
	DEBUGFS_FWSTATS_ADD(thermal, false_irq);
	DEBUGFS_FWSTATS_ADD(thermal, adc_source_unexpected);

	DEBUGFS_FWSTATS_ADD(calib, fail_count);

	DEBUGFS_FWSTATS_ADD(calib, calib_count);

	DEBUGFS_FWSTATS_ADD(roaming, rssi_level);

	DEBUGFS_FWSTATS_ADD(dfs, num_of_radar_detections);

	DEBUGFS_ADD(conf, moddir);
	DEBUGFS_ADD(radar_detection, moddir);
#ifdef CONFIG_CFG80211_CERTIFICATION_ONUS
	DEBUGFS_ADD(radar_debug_mode, moddir);
#endif
	DEBUGFS_ADD(dynamic_fw_traces, moddir);

	return 0;
}