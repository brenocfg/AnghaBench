#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
struct TYPE_6__ {int /*<<< orphan*/  dflt_fqid; int /*<<< orphan*/  err_fqid; } ;
struct TYPE_7__ {TYPE_2__ non_rx_params; } ;
struct fman_port_params {TYPE_3__ specific_params; } ;
struct fman_port_dts_params {int qman_channel_id; } ;
struct TYPE_5__ {int /*<<< orphan*/  major; } ;
struct fman_port {TYPE_4__* cfg; int /*<<< orphan*/  port_speed; int /*<<< orphan*/  port_type; TYPE_1__ rev_info; } ;
struct TYPE_8__ {int deq_high_priority; int /*<<< orphan*/  dflt_fqid; scalar_t__ deq_sp; int /*<<< orphan*/  err_fqid; int /*<<< orphan*/  tx_fifo_deq_pipeline_depth; } ;

/* Variables and functions */
 int QMI_DEQ_CFG_SUBPORTAL_MASK ; 
 int /*<<< orphan*/  get_dflt_fifo_deq_pipeline_depth (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void set_tx_dflt_cfg(struct fman_port *port,
			    struct fman_port_params *port_params,
			    struct fman_port_dts_params *dts_params)
{
	port->cfg->tx_fifo_deq_pipeline_depth =
		get_dflt_fifo_deq_pipeline_depth(port->rev_info.major,
						 port->port_type,
						 port->port_speed);
	port->cfg->err_fqid =
		port_params->specific_params.non_rx_params.err_fqid;
	port->cfg->deq_sp =
		(u8)(dts_params->qman_channel_id & QMI_DEQ_CFG_SUBPORTAL_MASK);
	port->cfg->dflt_fqid =
		port_params->specific_params.non_rx_params.dflt_fqid;
	port->cfg->deq_high_priority = true;
}