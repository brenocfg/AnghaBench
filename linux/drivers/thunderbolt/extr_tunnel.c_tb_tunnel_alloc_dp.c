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
struct tb_tunnel {struct tb_path** paths; struct tb_port* dst_port; struct tb_port* src_port; int /*<<< orphan*/  activate; int /*<<< orphan*/  init; } ;
struct tb_port {int /*<<< orphan*/  cap_adap; } ;
struct tb_path {int dummy; } ;
struct tb {int dummy; } ;

/* Variables and functions */
 size_t TB_DP_AUX_PATH_IN ; 
 size_t TB_DP_AUX_PATH_OUT ; 
 int /*<<< orphan*/  TB_DP_AUX_RX_HOPID ; 
 int /*<<< orphan*/  TB_DP_AUX_TX_HOPID ; 
 int /*<<< orphan*/  TB_DP_VIDEO_HOPID ; 
 size_t TB_DP_VIDEO_PATH_OUT ; 
 int /*<<< orphan*/  TB_TUNNEL_DP ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  tb_dp_activate ; 
 int /*<<< orphan*/  tb_dp_init_aux_path (struct tb_path*) ; 
 int /*<<< orphan*/  tb_dp_init_video_path (struct tb_path*,int) ; 
 int /*<<< orphan*/  tb_dp_xchg_caps ; 
 struct tb_path* tb_path_alloc (struct tb*,struct tb_port*,int /*<<< orphan*/ ,struct tb_port*,int /*<<< orphan*/ ,int,char*) ; 
 struct tb_tunnel* tb_tunnel_alloc (struct tb*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tb_tunnel_free (struct tb_tunnel*) ; 

struct tb_tunnel *tb_tunnel_alloc_dp(struct tb *tb, struct tb_port *in,
				     struct tb_port *out)
{
	struct tb_tunnel *tunnel;
	struct tb_path **paths;
	struct tb_path *path;

	if (WARN_ON(!in->cap_adap || !out->cap_adap))
		return NULL;

	tunnel = tb_tunnel_alloc(tb, 3, TB_TUNNEL_DP);
	if (!tunnel)
		return NULL;

	tunnel->init = tb_dp_xchg_caps;
	tunnel->activate = tb_dp_activate;
	tunnel->src_port = in;
	tunnel->dst_port = out;

	paths = tunnel->paths;

	path = tb_path_alloc(tb, in, TB_DP_VIDEO_HOPID, out, TB_DP_VIDEO_HOPID,
			     1, "Video");
	if (!path)
		goto err_free;
	tb_dp_init_video_path(path, false);
	paths[TB_DP_VIDEO_PATH_OUT] = path;

	path = tb_path_alloc(tb, in, TB_DP_AUX_TX_HOPID, out,
			     TB_DP_AUX_TX_HOPID, 1, "AUX TX");
	if (!path)
		goto err_free;
	tb_dp_init_aux_path(path);
	paths[TB_DP_AUX_PATH_OUT] = path;

	path = tb_path_alloc(tb, out, TB_DP_AUX_RX_HOPID, in,
			     TB_DP_AUX_RX_HOPID, 1, "AUX RX");
	if (!path)
		goto err_free;
	tb_dp_init_aux_path(path);
	paths[TB_DP_AUX_PATH_IN] = path;

	return tunnel;

err_free:
	tb_tunnel_free(tunnel);
	return NULL;
}