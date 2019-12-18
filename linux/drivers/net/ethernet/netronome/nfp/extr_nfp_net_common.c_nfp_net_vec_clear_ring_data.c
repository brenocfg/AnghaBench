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

/* Variables and functions */
 int /*<<< orphan*/  NFP_NET_CFG_RXR_ADDR (unsigned int) ; 
 int /*<<< orphan*/  NFP_NET_CFG_RXR_SZ (unsigned int) ; 
 int /*<<< orphan*/  NFP_NET_CFG_RXR_VEC (unsigned int) ; 
 int /*<<< orphan*/  NFP_NET_CFG_TXR_ADDR (unsigned int) ; 
 int /*<<< orphan*/  NFP_NET_CFG_TXR_SZ (unsigned int) ; 
 int /*<<< orphan*/  NFP_NET_CFG_TXR_VEC (unsigned int) ; 
 int /*<<< orphan*/  nn_writeb (struct nfp_net*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nn_writeq (struct nfp_net*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nfp_net_vec_clear_ring_data(struct nfp_net *nn, unsigned int idx)
{
	nn_writeq(nn, NFP_NET_CFG_RXR_ADDR(idx), 0);
	nn_writeb(nn, NFP_NET_CFG_RXR_SZ(idx), 0);
	nn_writeb(nn, NFP_NET_CFG_RXR_VEC(idx), 0);

	nn_writeq(nn, NFP_NET_CFG_TXR_ADDR(idx), 0);
	nn_writeb(nn, NFP_NET_CFG_TXR_SZ(idx), 0);
	nn_writeb(nn, NFP_NET_CFG_TXR_VEC(idx), 0);
}