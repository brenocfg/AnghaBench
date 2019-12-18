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
 int /*<<< orphan*/  NFP_NET_CFG_ICR (unsigned int) ; 
 int /*<<< orphan*/  NFP_NET_CFG_ICR_UNMASKED ; 
 int /*<<< orphan*/  nn_pci_flush (struct nfp_net*) ; 
 int /*<<< orphan*/  nn_writeb (struct nfp_net*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nfp_net_irq_unmask(struct nfp_net *nn, unsigned int entry_nr)
{
	nn_writeb(nn, NFP_NET_CFG_ICR(entry_nr), NFP_NET_CFG_ICR_UNMASKED);
	nn_pci_flush(nn);
}