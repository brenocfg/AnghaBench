#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct fman_port_params {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  data_align; } ;
struct fman_port_cfg {int tx_fifo_low_comf_level; int errata_A006320; int excessive_threshold_register; int fmbm_tfne_has_features; TYPE_2__ buffer_prefix_content; int /*<<< orphan*/  rx_fifo_thr; int /*<<< orphan*/  rx_pri_elevation; int /*<<< orphan*/  deq_byte_cnt; int /*<<< orphan*/  tx_fifo_deq_pipeline_depth; int /*<<< orphan*/  deq_prefetch_option; int /*<<< orphan*/  deq_type; int /*<<< orphan*/  rx_cut_end_bytes; int /*<<< orphan*/  color; int /*<<< orphan*/  dma_swap_data; } ;
struct TYPE_3__ {int major; int minor; } ;
struct fman_port {TYPE_1__ rev_info; int /*<<< orphan*/  max_port_fifo_size; struct fman_port_cfg* cfg; int /*<<< orphan*/  port_type; int /*<<< orphan*/  port_speed; } ;

/* Variables and functions */
 int /*<<< orphan*/  BMI_DEQUEUE_PIPELINE_DEPTH (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BMI_FIFO_THRESHOLD ; 
 int /*<<< orphan*/  BMI_PRIORITY_ELEVATION_LEVEL ; 
 int /*<<< orphan*/  DFLT_PORT_BUFFER_PREFIX_CONTEXT_DATA_ALIGN ; 
 int /*<<< orphan*/  DFLT_PORT_CUT_BYTES_FROM_END ; 
 int /*<<< orphan*/  DFLT_PORT_RX_FIFO_PRI_ELEVATION_LEV (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DFLT_PORT_RX_FIFO_THRESHOLD (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FMAN_PORT_COLOR_GREEN ; 
 int /*<<< orphan*/  FMAN_PORT_DEQ_BY_PRI ; 
 int /*<<< orphan*/  FMAN_PORT_DEQ_FULL_PREFETCH ; 
 int /*<<< orphan*/  FMAN_PORT_DMA_NO_SWAP ; 
 int /*<<< orphan*/  QMI_BYTE_COUNT_LEVEL_CONTROL (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void set_dflt_cfg(struct fman_port *port,
			 struct fman_port_params *port_params)
{
	struct fman_port_cfg *cfg = port->cfg;

	cfg->dma_swap_data = FMAN_PORT_DMA_NO_SWAP;
	cfg->color = FMAN_PORT_COLOR_GREEN;
	cfg->rx_cut_end_bytes = DFLT_PORT_CUT_BYTES_FROM_END;
	cfg->rx_pri_elevation = BMI_PRIORITY_ELEVATION_LEVEL;
	cfg->rx_fifo_thr = BMI_FIFO_THRESHOLD;
	cfg->tx_fifo_low_comf_level = (5 * 1024);
	cfg->deq_type = FMAN_PORT_DEQ_BY_PRI;
	cfg->deq_prefetch_option = FMAN_PORT_DEQ_FULL_PREFETCH;
	cfg->tx_fifo_deq_pipeline_depth =
		BMI_DEQUEUE_PIPELINE_DEPTH(port->port_type, port->port_speed);
	cfg->deq_byte_cnt = QMI_BYTE_COUNT_LEVEL_CONTROL(port->port_type);

	cfg->rx_pri_elevation =
		DFLT_PORT_RX_FIFO_PRI_ELEVATION_LEV(port->max_port_fifo_size);
	port->cfg->rx_fifo_thr =
		DFLT_PORT_RX_FIFO_THRESHOLD(port->rev_info.major,
					    port->max_port_fifo_size);

	if ((port->rev_info.major == 6) &&
	    ((port->rev_info.minor == 0) || (port->rev_info.minor == 3)))
		cfg->errata_A006320 = true;

	/* Excessive Threshold register - exists for pre-FMv3 chips only */
	if (port->rev_info.major < 6)
		cfg->excessive_threshold_register = true;
	else
		cfg->fmbm_tfne_has_features = true;

	cfg->buffer_prefix_content.data_align =
		DFLT_PORT_BUFFER_PREFIX_CONTEXT_DATA_ALIGN;
}