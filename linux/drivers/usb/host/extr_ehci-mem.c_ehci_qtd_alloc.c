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
struct ehci_qtd {int dummy; } ;
struct ehci_hcd {int /*<<< orphan*/  qtd_pool; } ;
typedef  int /*<<< orphan*/  gfp_t ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 struct ehci_qtd* dma_pool_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ehci_qtd_init (struct ehci_hcd*,struct ehci_qtd*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct ehci_qtd *ehci_qtd_alloc (struct ehci_hcd *ehci, gfp_t flags)
{
	struct ehci_qtd		*qtd;
	dma_addr_t		dma;

	qtd = dma_pool_alloc (ehci->qtd_pool, flags, &dma);
	if (qtd != NULL) {
		ehci_qtd_init(ehci, qtd, dma);
	}
	return qtd;
}