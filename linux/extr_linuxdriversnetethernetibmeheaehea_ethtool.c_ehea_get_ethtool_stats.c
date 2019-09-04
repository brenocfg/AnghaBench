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
typedef  int u64 ;
struct net_device {int dummy; } ;
struct ethtool_stats {int dummy; } ;
struct ehea_port {int sig_comp_iv; int resets; TYPE_2__* port_res; } ;
struct TYPE_3__ {scalar_t__ queue_stopped; scalar_t__ err_frame_crc; scalar_t__ err_ip_cksum; scalar_t__ err_tcp_cksum; scalar_t__ poll_receive_errors; } ;
struct TYPE_4__ {int swqe_refill_th; int /*<<< orphan*/  swqe_avail; TYPE_1__ p_stats; } ;

/* Variables and functions */
 int EHEA_MAX_PORT_RES ; 
 int /*<<< orphan*/  ETH_SS_STATS ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int ehea_get_sset_count (struct net_device*,int /*<<< orphan*/ ) ; 
 struct ehea_port* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void ehea_get_ethtool_stats(struct net_device *dev,
				     struct ethtool_stats *stats, u64 *data)
{
	int i, k, tmp;
	struct ehea_port *port = netdev_priv(dev);

	for (i = 0; i < ehea_get_sset_count(dev, ETH_SS_STATS); i++)
		data[i] = 0;
	i = 0;

	data[i++] = port->sig_comp_iv;
	data[i++] = port->port_res[0].swqe_refill_th;
	data[i++] = port->resets;

	for (k = 0, tmp = 0; k < EHEA_MAX_PORT_RES; k++)
		tmp += port->port_res[k].p_stats.poll_receive_errors;
	data[i++] = tmp;

	for (k = 0, tmp = 0; k < EHEA_MAX_PORT_RES; k++)
		tmp += port->port_res[k].p_stats.err_tcp_cksum;
	data[i++] = tmp;

	for (k = 0, tmp = 0; k < EHEA_MAX_PORT_RES; k++)
		tmp += port->port_res[k].p_stats.err_ip_cksum;
	data[i++] = tmp;

	for (k = 0, tmp = 0; k < EHEA_MAX_PORT_RES; k++)
		tmp += port->port_res[k].p_stats.err_frame_crc;
	data[i++] = tmp;

	for (k = 0, tmp = 0; k < EHEA_MAX_PORT_RES; k++)
		tmp += port->port_res[k].p_stats.queue_stopped;
	data[i++] = tmp;

	for (k = 0; k < 16; k++)
		data[i++] = atomic_read(&port->port_res[k].swqe_avail);
}