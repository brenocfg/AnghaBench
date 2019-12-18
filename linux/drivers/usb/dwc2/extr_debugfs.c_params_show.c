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
struct seq_file {struct dwc2_hsotg* private; } ;
struct dwc2_core_params {int /*<<< orphan*/ * g_tx_fifo_size; } ;
struct dwc2_hsotg {struct dwc2_core_params params; } ;

/* Variables and functions */
 int MAX_EPS_CHANNELS ; 
 int /*<<< orphan*/  ahbcfg ; 
 int /*<<< orphan*/  besl ; 
 int /*<<< orphan*/  dma_desc_enable ; 
 int /*<<< orphan*/  dma_desc_fs_enable ; 
 int /*<<< orphan*/  en_multiple_tx_fifo ; 
 int /*<<< orphan*/  enable_dynamic_fifo ; 
 int /*<<< orphan*/  external_id_pin_ctl ; 
 int /*<<< orphan*/  g_dma ; 
 int /*<<< orphan*/  g_dma_desc ; 
 int /*<<< orphan*/  g_np_tx_fifo_size ; 
 int /*<<< orphan*/  g_rx_fifo_size ; 
 int /*<<< orphan*/  hird_threshold ; 
 int /*<<< orphan*/  hird_threshold_en ; 
 int /*<<< orphan*/  host_channels ; 
 int /*<<< orphan*/  host_dma ; 
 int /*<<< orphan*/  host_ls_low_power_phy_clk ; 
 int /*<<< orphan*/  host_nperio_tx_fifo_size ; 
 int /*<<< orphan*/  host_perio_tx_fifo_size ; 
 int /*<<< orphan*/  host_rx_fifo_size ; 
 int /*<<< orphan*/  host_support_fs_ls_low_power ; 
 int /*<<< orphan*/  i2c_enable ; 
 int /*<<< orphan*/  ipg_isoc_en ; 
 int /*<<< orphan*/  lpm ; 
 int /*<<< orphan*/  lpm_clock_gating ; 
 int /*<<< orphan*/  max_packet_count ; 
 int /*<<< orphan*/  max_transfer_size ; 
 int /*<<< orphan*/  otg_cap ; 
 int /*<<< orphan*/  phy_type ; 
 int /*<<< orphan*/  phy_ulpi_ddr ; 
 int /*<<< orphan*/  phy_ulpi_ext_vbus ; 
 int /*<<< orphan*/  phy_utmi_width ; 
 int /*<<< orphan*/  power_down ; 
 int /*<<< orphan*/  print_param (struct seq_file*,struct dwc2_core_params*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_param_hex (struct seq_file*,struct dwc2_core_params*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reload_ctl ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  service_interval ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int /*<<< orphan*/  speed ; 
 int /*<<< orphan*/  ts_dline ; 
 int /*<<< orphan*/  uframe_sched ; 
 int /*<<< orphan*/  ulpi_fs_ls ; 

__attribute__((used)) static int params_show(struct seq_file *seq, void *v)
{
	struct dwc2_hsotg *hsotg = seq->private;
	struct dwc2_core_params *p = &hsotg->params;
	int i;

	print_param(seq, p, otg_cap);
	print_param(seq, p, dma_desc_enable);
	print_param(seq, p, dma_desc_fs_enable);
	print_param(seq, p, speed);
	print_param(seq, p, enable_dynamic_fifo);
	print_param(seq, p, en_multiple_tx_fifo);
	print_param(seq, p, host_rx_fifo_size);
	print_param(seq, p, host_nperio_tx_fifo_size);
	print_param(seq, p, host_perio_tx_fifo_size);
	print_param(seq, p, max_transfer_size);
	print_param(seq, p, max_packet_count);
	print_param(seq, p, host_channels);
	print_param(seq, p, phy_type);
	print_param(seq, p, phy_utmi_width);
	print_param(seq, p, phy_ulpi_ddr);
	print_param(seq, p, phy_ulpi_ext_vbus);
	print_param(seq, p, i2c_enable);
	print_param(seq, p, ipg_isoc_en);
	print_param(seq, p, ulpi_fs_ls);
	print_param(seq, p, host_support_fs_ls_low_power);
	print_param(seq, p, host_ls_low_power_phy_clk);
	print_param(seq, p, ts_dline);
	print_param(seq, p, reload_ctl);
	print_param_hex(seq, p, ahbcfg);
	print_param(seq, p, uframe_sched);
	print_param(seq, p, external_id_pin_ctl);
	print_param(seq, p, power_down);
	print_param(seq, p, lpm);
	print_param(seq, p, lpm_clock_gating);
	print_param(seq, p, besl);
	print_param(seq, p, hird_threshold_en);
	print_param(seq, p, hird_threshold);
	print_param(seq, p, service_interval);
	print_param(seq, p, host_dma);
	print_param(seq, p, g_dma);
	print_param(seq, p, g_dma_desc);
	print_param(seq, p, g_rx_fifo_size);
	print_param(seq, p, g_np_tx_fifo_size);

	for (i = 0; i < MAX_EPS_CHANNELS; i++) {
		char str[32];

		snprintf(str, 32, "g_tx_fifo_size[%d]", i);
		seq_printf(seq, "%-30s: %d\n", str, p->g_tx_fifo_size[i]);
	}

	return 0;
}