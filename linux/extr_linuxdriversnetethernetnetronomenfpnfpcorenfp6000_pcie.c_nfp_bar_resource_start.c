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
struct nfp_bar {int index; TYPE_1__* nfp; } ;
typedef  scalar_t__ resource_size_t ;
struct TYPE_2__ {int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 int nfp_bar_resource_len (struct nfp_bar*) ; 
 scalar_t__ pci_resource_start (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static resource_size_t nfp_bar_resource_start(struct nfp_bar *bar)
{
	return pci_resource_start(bar->nfp->pdev, (bar->index / 8) * 2)
		+ nfp_bar_resource_len(bar) * (bar->index & 7);
}