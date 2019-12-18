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
struct s390_domain {unsigned long* dma_table; int /*<<< orphan*/  dma_table_lock; } ;
struct TYPE_2__ {scalar_t__ aperture_start; scalar_t__ aperture_end; } ;
struct iommu_domain {TYPE_1__ geometry; } ;
typedef  unsigned long phys_addr_t ;
typedef  scalar_t__ dma_addr_t ;

/* Variables and functions */
 unsigned long ZPCI_PTE_ADDR_MASK ; 
 unsigned int calc_px (scalar_t__) ; 
 unsigned int calc_rtx (scalar_t__) ; 
 unsigned int calc_sx (scalar_t__) ; 
 unsigned long* get_rt_sto (unsigned long) ; 
 unsigned long* get_st_pto (unsigned long) ; 
 scalar_t__ pt_entry_isvalid (unsigned long) ; 
 scalar_t__ reg_entry_isvalid (unsigned long) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct s390_domain* to_s390_domain (struct iommu_domain*) ; 

__attribute__((used)) static phys_addr_t s390_iommu_iova_to_phys(struct iommu_domain *domain,
					   dma_addr_t iova)
{
	struct s390_domain *s390_domain = to_s390_domain(domain);
	unsigned long *sto, *pto, *rto, flags;
	unsigned int rtx, sx, px;
	phys_addr_t phys = 0;

	if (iova < domain->geometry.aperture_start ||
	    iova > domain->geometry.aperture_end)
		return 0;

	rtx = calc_rtx(iova);
	sx = calc_sx(iova);
	px = calc_px(iova);
	rto = s390_domain->dma_table;

	spin_lock_irqsave(&s390_domain->dma_table_lock, flags);
	if (rto && reg_entry_isvalid(rto[rtx])) {
		sto = get_rt_sto(rto[rtx]);
		if (sto && reg_entry_isvalid(sto[sx])) {
			pto = get_st_pto(sto[sx]);
			if (pto && pt_entry_isvalid(pto[px]))
				phys = pto[px] & ZPCI_PTE_ADDR_MASK;
		}
	}
	spin_unlock_irqrestore(&s390_domain->dma_table_lock, flags);

	return phys;
}