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
struct msm_priv {int /*<<< orphan*/  pgtlock; TYPE_1__* iop; } ;
struct iommu_domain {int dummy; } ;
typedef  int /*<<< orphan*/  phys_addr_t ;
struct TYPE_2__ {int (* map ) (TYPE_1__*,unsigned long,int /*<<< orphan*/ ,size_t,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int stub1 (TYPE_1__*,unsigned long,int /*<<< orphan*/ ,size_t,int) ; 
 struct msm_priv* to_msm_priv (struct iommu_domain*) ; 

__attribute__((used)) static int msm_iommu_map(struct iommu_domain *domain, unsigned long iova,
			 phys_addr_t pa, size_t len, int prot)
{
	struct msm_priv *priv = to_msm_priv(domain);
	unsigned long flags;
	int ret;

	spin_lock_irqsave(&priv->pgtlock, flags);
	ret = priv->iop->map(priv->iop, iova, pa, len, prot);
	spin_unlock_irqrestore(&priv->pgtlock, flags);

	return ret;
}