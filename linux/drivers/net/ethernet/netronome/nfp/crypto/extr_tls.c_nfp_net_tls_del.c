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
struct tls_context {int dummy; } ;
struct nfp_net_tls_offload_ctx {int /*<<< orphan*/  fw_handle; } ;
struct nfp_net {int dummy; } ;
struct net_device {int dummy; } ;
typedef  enum tls_offload_ctx_dir { ____Placeholder_tls_offload_ctx_dir } tls_offload_ctx_dir ;

/* Variables and functions */
 struct nfp_net_tls_offload_ctx* __tls_driver_ctx (struct tls_context*,int) ; 
 struct nfp_net* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  nfp_net_tls_conn_remove (struct nfp_net*,int) ; 
 int /*<<< orphan*/  nfp_net_tls_del_fw (struct nfp_net*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
nfp_net_tls_del(struct net_device *netdev, struct tls_context *tls_ctx,
		enum tls_offload_ctx_dir direction)
{
	struct nfp_net *nn = netdev_priv(netdev);
	struct nfp_net_tls_offload_ctx *ntls;

	nfp_net_tls_conn_remove(nn, direction);

	ntls = __tls_driver_ctx(tls_ctx, direction);
	nfp_net_tls_del_fw(nn, ntls->fw_handle);
}