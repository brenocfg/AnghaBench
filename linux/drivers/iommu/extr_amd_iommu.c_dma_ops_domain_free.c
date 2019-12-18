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
struct TYPE_2__ {scalar_t__ id; } ;
struct dma_ops_domain {TYPE_1__ domain; int /*<<< orphan*/  iovad; } ;

/* Variables and functions */
 int /*<<< orphan*/  domain_id_free (scalar_t__) ; 
 int /*<<< orphan*/  free_pagetable (TYPE_1__*) ; 
 int /*<<< orphan*/  kfree (struct dma_ops_domain*) ; 
 int /*<<< orphan*/  put_iova_domain (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dma_ops_domain_free(struct dma_ops_domain *dom)
{
	if (!dom)
		return;

	put_iova_domain(&dom->iovad);

	free_pagetable(&dom->domain);

	if (dom->domain.id)
		domain_id_free(dom->domain.id);

	kfree(dom);
}