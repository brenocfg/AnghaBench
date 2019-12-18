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
 int /*<<< orphan*/  DEBUGFS_ADD_PREFIX (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct dentry*) ; 
 int /*<<< orphan*/  always ; 
 int /*<<< orphan*/  beacon_filtering ; 
 int /*<<< orphan*/  beacon_interval ; 
 struct dentry* debugfs_create_dir (char*,struct dentry*) ; 
 int /*<<< orphan*/  dev ; 
 int /*<<< orphan*/  driver_state ; 
 int /*<<< orphan*/  dtim_interval ; 
 int /*<<< orphan*/  dynamic_ps_timeout ; 
 int /*<<< orphan*/  excessive_retries ; 
 int /*<<< orphan*/  forced_ps ; 
 int /*<<< orphan*/  fw_logger ; 
 int /*<<< orphan*/  fw_stats_raw ; 
 int /*<<< orphan*/  gpio_power ; 
 int /*<<< orphan*/  interval ; 
 int /*<<< orphan*/  irq_blk_threshold ; 
 int /*<<< orphan*/  irq_pkt_threshold ; 
 int /*<<< orphan*/  irq_timeout ; 
 int /*<<< orphan*/  mem ; 
 int /*<<< orphan*/  retry_count ; 
 int /*<<< orphan*/  rx_streaming ; 
 int /*<<< orphan*/  sleep_auth ; 
 int /*<<< orphan*/  split_scan_timeout ; 
 int /*<<< orphan*/  start_recovery ; 
 int /*<<< orphan*/  suspend_dtim_interval ; 
 int /*<<< orphan*/  tx_queue_len ; 
 int /*<<< orphan*/  vifs_state ; 

__attribute__((used)) static void wl1271_debugfs_add_files(struct wl1271 *wl,
				     struct dentry *rootdir)
{
	struct dentry *streaming;

	DEBUGFS_ADD(tx_queue_len, rootdir);
	DEBUGFS_ADD(retry_count, rootdir);
	DEBUGFS_ADD(excessive_retries, rootdir);

	DEBUGFS_ADD(gpio_power, rootdir);
	DEBUGFS_ADD(start_recovery, rootdir);
	DEBUGFS_ADD(driver_state, rootdir);
	DEBUGFS_ADD(vifs_state, rootdir);
	DEBUGFS_ADD(dtim_interval, rootdir);
	DEBUGFS_ADD(suspend_dtim_interval, rootdir);
	DEBUGFS_ADD(beacon_interval, rootdir);
	DEBUGFS_ADD(beacon_filtering, rootdir);
	DEBUGFS_ADD(dynamic_ps_timeout, rootdir);
	DEBUGFS_ADD(forced_ps, rootdir);
	DEBUGFS_ADD(split_scan_timeout, rootdir);
	DEBUGFS_ADD(irq_pkt_threshold, rootdir);
	DEBUGFS_ADD(irq_blk_threshold, rootdir);
	DEBUGFS_ADD(irq_timeout, rootdir);
	DEBUGFS_ADD(fw_stats_raw, rootdir);
	DEBUGFS_ADD(sleep_auth, rootdir);
	DEBUGFS_ADD(fw_logger, rootdir);

	streaming = debugfs_create_dir("rx_streaming", rootdir);

	DEBUGFS_ADD_PREFIX(rx_streaming, interval, streaming);
	DEBUGFS_ADD_PREFIX(rx_streaming, always, streaming);

	DEBUGFS_ADD_PREFIX(dev, mem, rootdir);
}