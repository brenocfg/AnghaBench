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
struct nfp_net {int dummy; } ;
typedef  enum tls_offload_ctx_dir { ____Placeholder_tls_offload_ctx_dir } tls_offload_ctx_dir ;

/* Variables and functions */
 int /*<<< orphan*/  NFP_NET_CFG_UPDATE_CRYPTO ; 
 int __nfp_net_reconfig (struct nfp_net*,int /*<<< orphan*/ ) ; 
 scalar_t__ __nfp_net_tls_conn_cnt_changed (struct nfp_net*,int,int) ; 
 int /*<<< orphan*/  nn_ctrl_bar_lock (struct nfp_net*) ; 
 int /*<<< orphan*/  nn_ctrl_bar_unlock (struct nfp_net*) ; 

__attribute__((used)) static int
nfp_net_tls_conn_cnt_changed(struct nfp_net *nn, int add,
			     enum tls_offload_ctx_dir direction)
{
	int ret = 0;

	/* Use the BAR lock to protect the connection counts */
	nn_ctrl_bar_lock(nn);
	if (__nfp_net_tls_conn_cnt_changed(nn, add, direction)) {
		ret = __nfp_net_reconfig(nn, NFP_NET_CFG_UPDATE_CRYPTO);
		/* Undo the cnt adjustment if failed */
		if (ret)
			__nfp_net_tls_conn_cnt_changed(nn, -add, direction);
	}
	nn_ctrl_bar_unlock(nn);

	return ret;
}