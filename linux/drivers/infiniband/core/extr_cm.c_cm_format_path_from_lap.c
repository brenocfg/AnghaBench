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
struct sa_path_rec {int reversible; scalar_t__ packet_life_time; void* packet_life_time_selector; int /*<<< orphan*/  rate; void* rate_selector; int /*<<< orphan*/  mtu; void* mtu_selector; int /*<<< orphan*/  sl; int /*<<< orphan*/  pkey; int /*<<< orphan*/  traffic_class; int /*<<< orphan*/  hop_limit; int /*<<< orphan*/  flow_label; int /*<<< orphan*/  sgid; int /*<<< orphan*/  dgid; } ;
struct cm_lap_msg {int /*<<< orphan*/  alt_hop_limit; int /*<<< orphan*/  alt_remote_gid; int /*<<< orphan*/  alt_local_gid; } ;
struct cm_id_private {int /*<<< orphan*/  path_mtu; int /*<<< orphan*/  pkey; } ;

/* Variables and functions */
 void* IB_SA_EQ ; 
 int /*<<< orphan*/  cm_format_path_lid_from_lap (struct cm_lap_msg*,struct sa_path_rec*) ; 
 int /*<<< orphan*/  cm_lap_get_flow_label (struct cm_lap_msg*) ; 
 scalar_t__ cm_lap_get_local_ack_timeout (struct cm_lap_msg*) ; 
 int /*<<< orphan*/  cm_lap_get_packet_rate (struct cm_lap_msg*) ; 
 int /*<<< orphan*/  cm_lap_get_sl (struct cm_lap_msg*) ; 
 int /*<<< orphan*/  cm_lap_get_traffic_class (struct cm_lap_msg*) ; 

__attribute__((used)) static void cm_format_path_from_lap(struct cm_id_private *cm_id_priv,
				    struct sa_path_rec *path,
				    struct cm_lap_msg *lap_msg)
{
	path->dgid = lap_msg->alt_local_gid;
	path->sgid = lap_msg->alt_remote_gid;
	path->flow_label = cm_lap_get_flow_label(lap_msg);
	path->hop_limit = lap_msg->alt_hop_limit;
	path->traffic_class = cm_lap_get_traffic_class(lap_msg);
	path->reversible = 1;
	path->pkey = cm_id_priv->pkey;
	path->sl = cm_lap_get_sl(lap_msg);
	path->mtu_selector = IB_SA_EQ;
	path->mtu = cm_id_priv->path_mtu;
	path->rate_selector = IB_SA_EQ;
	path->rate = cm_lap_get_packet_rate(lap_msg);
	path->packet_life_time_selector = IB_SA_EQ;
	path->packet_life_time = cm_lap_get_local_ack_timeout(lap_msg);
	path->packet_life_time -= (path->packet_life_time > 0);
	cm_format_path_lid_from_lap(lap_msg, path);
}