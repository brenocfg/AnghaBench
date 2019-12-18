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
struct iommu_domain {int dummy; } ;
struct qcom_iommu_domain {struct iommu_domain domain; int /*<<< orphan*/  pgtbl_lock; int /*<<< orphan*/  init_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 unsigned int IOMMU_DOMAIN_DMA ; 
 unsigned int IOMMU_DOMAIN_UNMANAGED ; 
 scalar_t__ iommu_get_dma_cookie (struct iommu_domain*) ; 
 int /*<<< orphan*/  kfree (struct qcom_iommu_domain*) ; 
 struct qcom_iommu_domain* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct iommu_domain *qcom_iommu_domain_alloc(unsigned type)
{
	struct qcom_iommu_domain *qcom_domain;

	if (type != IOMMU_DOMAIN_UNMANAGED && type != IOMMU_DOMAIN_DMA)
		return NULL;
	/*
	 * Allocate the domain and initialise some of its data structures.
	 * We can't really do anything meaningful until we've added a
	 * master.
	 */
	qcom_domain = kzalloc(sizeof(*qcom_domain), GFP_KERNEL);
	if (!qcom_domain)
		return NULL;

	if (type == IOMMU_DOMAIN_DMA &&
	    iommu_get_dma_cookie(&qcom_domain->domain)) {
		kfree(qcom_domain);
		return NULL;
	}

	mutex_init(&qcom_domain->init_mutex);
	spin_lock_init(&qcom_domain->pgtbl_lock);

	return &qcom_domain->domain;
}