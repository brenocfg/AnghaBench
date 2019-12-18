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
struct nfp_pf {int /*<<< orphan*/  irq_entries; int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfp_net_irqs_disable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nfp_net_pf_free_irqs(struct nfp_pf *pf)
{
	nfp_net_irqs_disable(pf->pdev);
	kfree(pf->irq_entries);
}