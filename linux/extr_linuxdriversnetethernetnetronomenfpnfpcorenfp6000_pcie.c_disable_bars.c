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
struct nfp_bar {int /*<<< orphan*/ * iomem; } ;
struct nfp6000_pcie {int bars; struct nfp_bar* bar; } ;

/* Variables and functions */
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void disable_bars(struct nfp6000_pcie *nfp)
{
	struct nfp_bar *bar = &nfp->bar[0];
	int n;

	for (n = 0; n < nfp->bars; n++, bar++) {
		if (bar->iomem) {
			iounmap(bar->iomem);
			bar->iomem = NULL;
		}
	}
}