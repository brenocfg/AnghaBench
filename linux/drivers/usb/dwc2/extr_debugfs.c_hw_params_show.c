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
struct dwc2_hw_params {int dummy; } ;
struct dwc2_hsotg {struct dwc2_hw_params hw_params; } ;

/* Variables and functions */
 int /*<<< orphan*/  arch ; 
 int /*<<< orphan*/  dev_ep_dirs ; 
 int /*<<< orphan*/  dev_nperio_tx_fifo_size ; 
 int /*<<< orphan*/  dev_token_q_depth ; 
 int /*<<< orphan*/  dma_desc_enable ; 
 int /*<<< orphan*/  en_multiple_tx_fifo ; 
 int /*<<< orphan*/  enable_dynamic_fifo ; 
 int /*<<< orphan*/  fs_phy_type ; 
 int /*<<< orphan*/  host_channels ; 
 int /*<<< orphan*/  host_nperio_tx_fifo_size ; 
 int /*<<< orphan*/  host_perio_tx_fifo_size ; 
 int /*<<< orphan*/  host_perio_tx_q_depth ; 
 int /*<<< orphan*/  hs_phy_type ; 
 int /*<<< orphan*/  i2c_enable ; 
 int /*<<< orphan*/  max_packet_count ; 
 int /*<<< orphan*/  max_transfer_size ; 
 int /*<<< orphan*/  nperio_tx_q_depth ; 
 int /*<<< orphan*/  num_dev_ep ; 
 int /*<<< orphan*/  num_dev_perio_in_ep ; 
 int /*<<< orphan*/  op_mode ; 
 int /*<<< orphan*/  power_optimized ; 
 int /*<<< orphan*/  print_param (struct seq_file*,struct dwc2_hw_params*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_param_hex (struct seq_file*,struct dwc2_hw_params*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rx_fifo_size ; 
 int /*<<< orphan*/  snpsid ; 
 int /*<<< orphan*/  total_fifo_size ; 
 int /*<<< orphan*/  utmi_phy_data_width ; 

__attribute__((used)) static int hw_params_show(struct seq_file *seq, void *v)
{
	struct dwc2_hsotg *hsotg = seq->private;
	struct dwc2_hw_params *hw = &hsotg->hw_params;

	print_param(seq, hw, op_mode);
	print_param(seq, hw, arch);
	print_param(seq, hw, dma_desc_enable);
	print_param(seq, hw, enable_dynamic_fifo);
	print_param(seq, hw, en_multiple_tx_fifo);
	print_param(seq, hw, rx_fifo_size);
	print_param(seq, hw, host_nperio_tx_fifo_size);
	print_param(seq, hw, dev_nperio_tx_fifo_size);
	print_param(seq, hw, host_perio_tx_fifo_size);
	print_param(seq, hw, nperio_tx_q_depth);
	print_param(seq, hw, host_perio_tx_q_depth);
	print_param(seq, hw, dev_token_q_depth);
	print_param(seq, hw, max_transfer_size);
	print_param(seq, hw, max_packet_count);
	print_param(seq, hw, host_channels);
	print_param(seq, hw, hs_phy_type);
	print_param(seq, hw, fs_phy_type);
	print_param(seq, hw, i2c_enable);
	print_param(seq, hw, num_dev_ep);
	print_param(seq, hw, num_dev_perio_in_ep);
	print_param(seq, hw, total_fifo_size);
	print_param(seq, hw, power_optimized);
	print_param(seq, hw, utmi_phy_data_width);
	print_param_hex(seq, hw, snpsid);
	print_param_hex(seq, hw, dev_ep_dirs);

	return 0;
}