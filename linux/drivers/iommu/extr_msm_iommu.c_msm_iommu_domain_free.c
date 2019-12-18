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
struct msm_priv {int dummy; } ;
struct iommu_domain {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct msm_priv*) ; 
 int /*<<< orphan*/  msm_iommu_lock ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct msm_priv* to_msm_priv (struct iommu_domain*) ; 

__attribute__((used)) static void msm_iommu_domain_free(struct iommu_domain *domain)
{
	struct msm_priv *priv;
	unsigned long flags;

	spin_lock_irqsave(&msm_iommu_lock, flags);
	priv = to_msm_priv(domain);
	kfree(priv);
	spin_unlock_irqrestore(&msm_iommu_lock, flags);
}