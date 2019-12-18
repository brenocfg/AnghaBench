#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct tb_tunnel {int /*<<< orphan*/  dst_port; int /*<<< orphan*/  src_port; struct tb_path** paths; } ;
struct tb_path {int path_length; TYPE_1__* hops; } ;
struct TYPE_2__ {int /*<<< orphan*/  next_hop_index; int /*<<< orphan*/  in_hop_index; } ;

/* Variables and functions */
 size_t TB_DP_AUX_PATH_IN ; 
 size_t TB_DP_AUX_PATH_OUT ; 
 size_t TB_DP_VIDEO_PATH_OUT ; 
 int tb_dp_port_enable (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tb_dp_port_hpd_clear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tb_dp_port_set_hops (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ tb_port_is_dpout (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tb_dp_activate(struct tb_tunnel *tunnel, bool active)
{
	int ret;

	if (active) {
		struct tb_path **paths;
		int last;

		paths = tunnel->paths;
		last = paths[TB_DP_VIDEO_PATH_OUT]->path_length - 1;

		tb_dp_port_set_hops(tunnel->src_port,
			paths[TB_DP_VIDEO_PATH_OUT]->hops[0].in_hop_index,
			paths[TB_DP_AUX_PATH_OUT]->hops[0].in_hop_index,
			paths[TB_DP_AUX_PATH_IN]->hops[last].next_hop_index);

		tb_dp_port_set_hops(tunnel->dst_port,
			paths[TB_DP_VIDEO_PATH_OUT]->hops[last].next_hop_index,
			paths[TB_DP_AUX_PATH_IN]->hops[0].in_hop_index,
			paths[TB_DP_AUX_PATH_OUT]->hops[last].next_hop_index);
	} else {
		tb_dp_port_hpd_clear(tunnel->src_port);
		tb_dp_port_set_hops(tunnel->src_port, 0, 0, 0);
		if (tb_port_is_dpout(tunnel->dst_port))
			tb_dp_port_set_hops(tunnel->dst_port, 0, 0, 0);
	}

	ret = tb_dp_port_enable(tunnel->src_port, active);
	if (ret)
		return ret;

	if (tb_port_is_dpout(tunnel->dst_port))
		return tb_dp_port_enable(tunnel->dst_port, active);

	return 0;
}