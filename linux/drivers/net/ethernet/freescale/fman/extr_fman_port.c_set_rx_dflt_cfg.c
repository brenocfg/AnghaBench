#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  pcd_fqs_count; int /*<<< orphan*/  pcd_base_fqid; int /*<<< orphan*/  dflt_fqid; int /*<<< orphan*/  err_fqid; int /*<<< orphan*/  ext_buf_pools; } ;
struct TYPE_6__ {TYPE_2__ rx_params; } ;
struct fman_port_params {TYPE_3__ specific_params; } ;
struct fman_port {TYPE_1__* cfg; } ;
struct fman_ext_pools {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  pcd_fqs_count; int /*<<< orphan*/  pcd_base_fqid; int /*<<< orphan*/  dflt_fqid; int /*<<< orphan*/  err_fqid; int /*<<< orphan*/  ext_buf_pools; int /*<<< orphan*/  discard_mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  DFLT_PORT_ERRORS_TO_DISCARD ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void set_rx_dflt_cfg(struct fman_port *port,
			    struct fman_port_params *port_params)
{
	port->cfg->discard_mask = DFLT_PORT_ERRORS_TO_DISCARD;

	memcpy(&port->cfg->ext_buf_pools,
	       &port_params->specific_params.rx_params.ext_buf_pools,
	       sizeof(struct fman_ext_pools));
	port->cfg->err_fqid =
		port_params->specific_params.rx_params.err_fqid;
	port->cfg->dflt_fqid =
		port_params->specific_params.rx_params.dflt_fqid;
	port->cfg->pcd_base_fqid =
		port_params->specific_params.rx_params.pcd_base_fqid;
	port->cfg->pcd_fqs_count =
		port_params->specific_params.rx_params.pcd_fqs_count;
}