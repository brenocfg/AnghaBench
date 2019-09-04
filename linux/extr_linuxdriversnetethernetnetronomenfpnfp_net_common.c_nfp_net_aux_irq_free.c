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
typedef  int /*<<< orphan*/  u32 ;
struct nfp_net {TYPE_1__* irq_entries; } ;
struct TYPE_2__ {int /*<<< orphan*/  vector; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct nfp_net*) ; 
 int /*<<< orphan*/  nn_pci_flush (struct nfp_net*) ; 
 int /*<<< orphan*/  nn_writeb (struct nfp_net*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void nfp_net_aux_irq_free(struct nfp_net *nn, u32 ctrl_offset,
				 unsigned int vector_idx)
{
	nn_writeb(nn, ctrl_offset, 0xff);
	nn_pci_flush(nn);
	free_irq(nn->irq_entries[vector_idx].vector, nn);
}