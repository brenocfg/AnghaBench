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
 int /*<<< orphan*/  DEBUGFS_FWSTATS_ADD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* KBUILD_MODNAME ; 
 int /*<<< orphan*/  addr_key_count ; 
 int /*<<< orphan*/  aes ; 
 int /*<<< orphan*/  beacon_buffer_thres_host_int_trig_rx_data ; 
 int /*<<< orphan*/  calc_failure ; 
 int /*<<< orphan*/  calibration ; 
 int /*<<< orphan*/  cmd_cmplt ; 
 int /*<<< orphan*/  commands ; 
 struct dentry* debugfs_create_dir (char*,struct dentry*) ; 
 int /*<<< orphan*/  decrypt_done ; 
 int /*<<< orphan*/  decrypt_fail ; 
 int /*<<< orphan*/  decrypt_interrupt ; 
 int /*<<< orphan*/  decrypt_packets ; 
 int /*<<< orphan*/  default_key_count ; 
 int /*<<< orphan*/  descr_host_int_trig_rx_data ; 
 int /*<<< orphan*/  disable_ps ; 
 int /*<<< orphan*/  dma ; 
 int /*<<< orphan*/  dma0_done ; 
 int /*<<< orphan*/  dma1_done ; 
 int /*<<< orphan*/  dropped ; 
 int /*<<< orphan*/  elp_enter ; 
 int /*<<< orphan*/  enable_ps ; 
 int /*<<< orphan*/  encrypt_fail ; 
 int /*<<< orphan*/  encrypt_interrupt ; 
 int /*<<< orphan*/  encrypt_packets ; 
 int /*<<< orphan*/  event ; 
 int /*<<< orphan*/  fcs_err ; 
 int /*<<< orphan*/  fiqs ; 
 int /*<<< orphan*/  fix_tsf_ps ; 
 int /*<<< orphan*/  hdr_overflow ; 
 int /*<<< orphan*/  heart_beat ; 
 int /*<<< orphan*/  host_acknowledges ; 
 int /*<<< orphan*/  hw_pm_mode_changes ; 
 int /*<<< orphan*/  hw_stuck ; 
 int /*<<< orphan*/  internal_desc_overflow ; 
 int /*<<< orphan*/  interrupt ; 
 int /*<<< orphan*/  irqs ; 
 int /*<<< orphan*/  isr ; 
 int /*<<< orphan*/  key_not_found ; 
 int /*<<< orphan*/  low_rssi ; 
 int /*<<< orphan*/  mic ; 
 int /*<<< orphan*/  missed_beacon_host_int_trig_rx_data ; 
 int /*<<< orphan*/  missing_bcns ; 
 int /*<<< orphan*/  oom_late ; 
 int /*<<< orphan*/  out_of_mem ; 
 int /*<<< orphan*/  packets ; 
 int /*<<< orphan*/  path_reset ; 
 int /*<<< orphan*/  pci_pm ; 
 int /*<<< orphan*/  phy_transmit_error ; 
 int /*<<< orphan*/  power_save_off ; 
 int /*<<< orphan*/  ps ; 
 int /*<<< orphan*/  ps_enter ; 
 int /*<<< orphan*/  pspoll_max_apturn ; 
 int /*<<< orphan*/  pspoll_timeouts ; 
 int /*<<< orphan*/  pspoll_utilization ; 
 int /*<<< orphan*/  pwr ; 
 int /*<<< orphan*/  rcvd_awake_beacons ; 
 int /*<<< orphan*/  rcvd_beacons ; 
 int /*<<< orphan*/  reset_counter ; 
 int /*<<< orphan*/  rx ; 
 int /*<<< orphan*/  rx_errors ; 
 int /*<<< orphan*/  rx_headers ; 
 int /*<<< orphan*/  rx_mem_empty ; 
 int /*<<< orphan*/  rx_mem_overflow ; 
 int /*<<< orphan*/  rx_mismatch ; 
 int /*<<< orphan*/  rx_pkts ; 
 int /*<<< orphan*/  rx_pool ; 
 int /*<<< orphan*/  rx_prep_beacon_drop ; 
 int /*<<< orphan*/  rx_procs ; 
 int /*<<< orphan*/  rx_rdys ; 
 int /*<<< orphan*/  rx_requested ; 
 int /*<<< orphan*/  rxpipe ; 
 int /*<<< orphan*/  tx ; 
 int /*<<< orphan*/  tx_errors ; 
 int /*<<< orphan*/  tx_exch_complete ; 
 int /*<<< orphan*/  tx_procs ; 
 int /*<<< orphan*/  tx_requested ; 
 int /*<<< orphan*/  tx_stuck ; 
 int /*<<< orphan*/  tx_with_ps ; 
 int /*<<< orphan*/  tx_without_ps ; 
 int /*<<< orphan*/  tx_xfr_host_int_trig_rx_data ; 
 int /*<<< orphan*/  upsd_max_apturn ; 
 int /*<<< orphan*/  upsd_max_sptime ; 
 int /*<<< orphan*/  upsd_timeouts ; 
 int /*<<< orphan*/  upsd_utilization ; 
 int /*<<< orphan*/  wake_on_host ; 
 int /*<<< orphan*/  wake_on_timer_exp ; 
 int /*<<< orphan*/  wakeups ; 
 int /*<<< orphan*/  wep ; 
 int /*<<< orphan*/  xfr_hint_trig ; 

int wl12xx_debugfs_add_files(struct wl1271 *wl,
			     struct dentry *rootdir)
{
	struct dentry *stats, *moddir;

	moddir = debugfs_create_dir(KBUILD_MODNAME, rootdir);
	stats = debugfs_create_dir("fw_stats", moddir);

	DEBUGFS_FWSTATS_ADD(tx, internal_desc_overflow);

	DEBUGFS_FWSTATS_ADD(rx, out_of_mem);
	DEBUGFS_FWSTATS_ADD(rx, hdr_overflow);
	DEBUGFS_FWSTATS_ADD(rx, hw_stuck);
	DEBUGFS_FWSTATS_ADD(rx, dropped);
	DEBUGFS_FWSTATS_ADD(rx, fcs_err);
	DEBUGFS_FWSTATS_ADD(rx, xfr_hint_trig);
	DEBUGFS_FWSTATS_ADD(rx, path_reset);
	DEBUGFS_FWSTATS_ADD(rx, reset_counter);

	DEBUGFS_FWSTATS_ADD(dma, rx_requested);
	DEBUGFS_FWSTATS_ADD(dma, rx_errors);
	DEBUGFS_FWSTATS_ADD(dma, tx_requested);
	DEBUGFS_FWSTATS_ADD(dma, tx_errors);

	DEBUGFS_FWSTATS_ADD(isr, cmd_cmplt);
	DEBUGFS_FWSTATS_ADD(isr, fiqs);
	DEBUGFS_FWSTATS_ADD(isr, rx_headers);
	DEBUGFS_FWSTATS_ADD(isr, rx_mem_overflow);
	DEBUGFS_FWSTATS_ADD(isr, rx_rdys);
	DEBUGFS_FWSTATS_ADD(isr, irqs);
	DEBUGFS_FWSTATS_ADD(isr, tx_procs);
	DEBUGFS_FWSTATS_ADD(isr, decrypt_done);
	DEBUGFS_FWSTATS_ADD(isr, dma0_done);
	DEBUGFS_FWSTATS_ADD(isr, dma1_done);
	DEBUGFS_FWSTATS_ADD(isr, tx_exch_complete);
	DEBUGFS_FWSTATS_ADD(isr, commands);
	DEBUGFS_FWSTATS_ADD(isr, rx_procs);
	DEBUGFS_FWSTATS_ADD(isr, hw_pm_mode_changes);
	DEBUGFS_FWSTATS_ADD(isr, host_acknowledges);
	DEBUGFS_FWSTATS_ADD(isr, pci_pm);
	DEBUGFS_FWSTATS_ADD(isr, wakeups);
	DEBUGFS_FWSTATS_ADD(isr, low_rssi);

	DEBUGFS_FWSTATS_ADD(wep, addr_key_count);
	DEBUGFS_FWSTATS_ADD(wep, default_key_count);
	/* skipping wep.reserved */
	DEBUGFS_FWSTATS_ADD(wep, key_not_found);
	DEBUGFS_FWSTATS_ADD(wep, decrypt_fail);
	DEBUGFS_FWSTATS_ADD(wep, packets);
	DEBUGFS_FWSTATS_ADD(wep, interrupt);

	DEBUGFS_FWSTATS_ADD(pwr, ps_enter);
	DEBUGFS_FWSTATS_ADD(pwr, elp_enter);
	DEBUGFS_FWSTATS_ADD(pwr, missing_bcns);
	DEBUGFS_FWSTATS_ADD(pwr, wake_on_host);
	DEBUGFS_FWSTATS_ADD(pwr, wake_on_timer_exp);
	DEBUGFS_FWSTATS_ADD(pwr, tx_with_ps);
	DEBUGFS_FWSTATS_ADD(pwr, tx_without_ps);
	DEBUGFS_FWSTATS_ADD(pwr, rcvd_beacons);
	DEBUGFS_FWSTATS_ADD(pwr, power_save_off);
	DEBUGFS_FWSTATS_ADD(pwr, enable_ps);
	DEBUGFS_FWSTATS_ADD(pwr, disable_ps);
	DEBUGFS_FWSTATS_ADD(pwr, fix_tsf_ps);
	/* skipping cont_miss_bcns_spread for now */
	DEBUGFS_FWSTATS_ADD(pwr, rcvd_awake_beacons);

	DEBUGFS_FWSTATS_ADD(mic, rx_pkts);
	DEBUGFS_FWSTATS_ADD(mic, calc_failure);

	DEBUGFS_FWSTATS_ADD(aes, encrypt_fail);
	DEBUGFS_FWSTATS_ADD(aes, decrypt_fail);
	DEBUGFS_FWSTATS_ADD(aes, encrypt_packets);
	DEBUGFS_FWSTATS_ADD(aes, decrypt_packets);
	DEBUGFS_FWSTATS_ADD(aes, encrypt_interrupt);
	DEBUGFS_FWSTATS_ADD(aes, decrypt_interrupt);

	DEBUGFS_FWSTATS_ADD(event, heart_beat);
	DEBUGFS_FWSTATS_ADD(event, calibration);
	DEBUGFS_FWSTATS_ADD(event, rx_mismatch);
	DEBUGFS_FWSTATS_ADD(event, rx_mem_empty);
	DEBUGFS_FWSTATS_ADD(event, rx_pool);
	DEBUGFS_FWSTATS_ADD(event, oom_late);
	DEBUGFS_FWSTATS_ADD(event, phy_transmit_error);
	DEBUGFS_FWSTATS_ADD(event, tx_stuck);

	DEBUGFS_FWSTATS_ADD(ps, pspoll_timeouts);
	DEBUGFS_FWSTATS_ADD(ps, upsd_timeouts);
	DEBUGFS_FWSTATS_ADD(ps, upsd_max_sptime);
	DEBUGFS_FWSTATS_ADD(ps, upsd_max_apturn);
	DEBUGFS_FWSTATS_ADD(ps, pspoll_max_apturn);
	DEBUGFS_FWSTATS_ADD(ps, pspoll_utilization);
	DEBUGFS_FWSTATS_ADD(ps, upsd_utilization);

	DEBUGFS_FWSTATS_ADD(rxpipe, rx_prep_beacon_drop);
	DEBUGFS_FWSTATS_ADD(rxpipe, descr_host_int_trig_rx_data);
	DEBUGFS_FWSTATS_ADD(rxpipe, beacon_buffer_thres_host_int_trig_rx_data);
	DEBUGFS_FWSTATS_ADD(rxpipe, missed_beacon_host_int_trig_rx_data);
	DEBUGFS_FWSTATS_ADD(rxpipe, tx_xfr_host_int_trig_rx_data);

	return 0;
}