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
typedef  scalar_t__ u32 ;
struct dwc2_hw_params {scalar_t__ total_fifo_size; scalar_t__ host_channels; } ;
struct dwc2_core_params {scalar_t__ host_rx_fifo_size; scalar_t__ host_nperio_tx_fifo_size; scalar_t__ host_perio_tx_fifo_size; } ;
struct dwc2_hsotg {int /*<<< orphan*/  dev; struct dwc2_hw_params hw_params; struct dwc2_core_params params; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void dwc2_calculate_dynamic_fifo(struct dwc2_hsotg *hsotg)
{
	struct dwc2_core_params *params = &hsotg->params;
	struct dwc2_hw_params *hw = &hsotg->hw_params;
	u32 rxfsiz, nptxfsiz, ptxfsiz, total_fifo_size;

	total_fifo_size = hw->total_fifo_size;
	rxfsiz = params->host_rx_fifo_size;
	nptxfsiz = params->host_nperio_tx_fifo_size;
	ptxfsiz = params->host_perio_tx_fifo_size;

	/*
	 * Will use Method 2 defined in the DWC2 spec: minimum FIFO depth
	 * allocation with support for high bandwidth endpoints. Synopsys
	 * defines MPS(Max Packet size) for a periodic EP=1024, and for
	 * non-periodic as 512.
	 */
	if (total_fifo_size < (rxfsiz + nptxfsiz + ptxfsiz)) {
		/*
		 * For Buffer DMA mode/Scatter Gather DMA mode
		 * 2 * ((Largest Packet size / 4) + 1 + 1) + n
		 * with n = number of host channel.
		 * 2 * ((1024/4) + 2) = 516
		 */
		rxfsiz = 516 + hw->host_channels;

		/*
		 * min non-periodic tx fifo depth
		 * 2 * (largest non-periodic USB packet used / 4)
		 * 2 * (512/4) = 256
		 */
		nptxfsiz = 256;

		/*
		 * min periodic tx fifo depth
		 * (largest packet size*MC)/4
		 * (1024 * 3)/4 = 768
		 */
		ptxfsiz = 768;

		params->host_rx_fifo_size = rxfsiz;
		params->host_nperio_tx_fifo_size = nptxfsiz;
		params->host_perio_tx_fifo_size = ptxfsiz;
	}

	/*
	 * If the summation of RX, NPTX and PTX fifo sizes is still
	 * bigger than the total_fifo_size, then we have a problem.
	 *
	 * We won't be able to allocate as many endpoints. Right now,
	 * we're just printing an error message, but ideally this FIFO
	 * allocation algorithm would be improved in the future.
	 *
	 * FIXME improve this FIFO allocation algorithm.
	 */
	if (unlikely(total_fifo_size < (rxfsiz + nptxfsiz + ptxfsiz)))
		dev_err(hsotg->dev, "invalid fifo sizes\n");
}