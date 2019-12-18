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
typedef  int /*<<< orphan*/  u8 ;
struct nfp_net {int dummy; } ;

/* Variables and functions */
 scalar_t__ NFP_NET_CFG_MACADDR ; 
 int /*<<< orphan*/  get_unaligned_be16 (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  get_unaligned_be32 (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  nn_writel (struct nfp_net*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nn_writew (struct nfp_net*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nfp_net_write_mac_addr(struct nfp_net *nn, const u8 *addr)
{
	nn_writel(nn, NFP_NET_CFG_MACADDR + 0, get_unaligned_be32(addr));
	nn_writew(nn, NFP_NET_CFG_MACADDR + 6, get_unaligned_be16(addr + 4));
}