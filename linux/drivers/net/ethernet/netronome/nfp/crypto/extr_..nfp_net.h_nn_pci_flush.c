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
 int /*<<< orphan*/  NFP_NET_CFG_VERSION ; 
 int /*<<< orphan*/  nn_readl (struct nfp_net*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void nn_pci_flush(struct nfp_net *nn)
{
	nn_readl(nn, NFP_NET_CFG_VERSION);
}