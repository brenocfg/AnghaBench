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
struct wmi_link_stats_global {int /*<<< orphan*/  tx_fail_no_ack; int /*<<< orphan*/  rx_crc_errors; int /*<<< orphan*/  rx_mic_errors; int /*<<< orphan*/  tx_beacons; int /*<<< orphan*/  tx_ba_frames; int /*<<< orphan*/  rx_ba_frames; int /*<<< orphan*/  tx_frames; int /*<<< orphan*/  rx_frames; } ;
struct wil6210_priv {int dummy; } ;
struct seq_file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wil_link_stats_print_global(struct wil6210_priv *wil,
					struct seq_file *s,
					struct wmi_link_stats_global *global)
{
	seq_printf(s, "Frames(rx:tx) %d:%d\n"
		   "BA Frames(rx:tx) %d:%d\n"
		   "Beacons %d\n"
		   "Rx Errors (MIC:CRC) %d:%d\n"
		   "Tx Errors (no ack) %d\n",
		   le32_to_cpu(global->rx_frames),
		   le32_to_cpu(global->tx_frames),
		   le32_to_cpu(global->rx_ba_frames),
		   le32_to_cpu(global->tx_ba_frames),
		   le32_to_cpu(global->tx_beacons),
		   le32_to_cpu(global->rx_mic_errors),
		   le32_to_cpu(global->rx_crc_errors),
		   le32_to_cpu(global->tx_fail_no_ack));
}