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
struct iova {int dummy; } ;
struct imgu_device {int /*<<< orphan*/  iova_domain; int /*<<< orphan*/  mmu; } ;
struct imgu_css_map {int /*<<< orphan*/  daddr; } ;

/* Variables and functions */
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  __free_iova (int /*<<< orphan*/ *,struct iova*) ; 
 struct iova* find_iova (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  imgu_mmu_unmap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  iova_dma_addr (int /*<<< orphan*/ *,struct iova*) ; 
 int /*<<< orphan*/  iova_pfn (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int iova_shift (int /*<<< orphan*/ *) ; 
 int iova_size (struct iova*) ; 

void imgu_dmamap_unmap(struct imgu_device *imgu, struct imgu_css_map *map)
{
	struct iova *iova;

	iova = find_iova(&imgu->iova_domain,
			 iova_pfn(&imgu->iova_domain, map->daddr));
	if (WARN_ON(!iova))
		return;

	imgu_mmu_unmap(imgu->mmu, iova_dma_addr(&imgu->iova_domain, iova),
		       iova_size(iova) << iova_shift(&imgu->iova_domain));

	__free_iova(&imgu->iova_domain, iova);
}