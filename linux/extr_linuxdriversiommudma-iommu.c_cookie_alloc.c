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
struct iommu_dma_cookie {int type; int /*<<< orphan*/  msi_page_list; int /*<<< orphan*/  msi_lock; } ;
typedef  enum iommu_dma_cookie_type { ____Placeholder_iommu_dma_cookie_type } iommu_dma_cookie_type ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 struct iommu_dma_cookie* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct iommu_dma_cookie *cookie_alloc(enum iommu_dma_cookie_type type)
{
	struct iommu_dma_cookie *cookie;

	cookie = kzalloc(sizeof(*cookie), GFP_KERNEL);
	if (cookie) {
		spin_lock_init(&cookie->msi_lock);
		INIT_LIST_HEAD(&cookie->msi_page_list);
		cookie->type = type;
	}
	return cookie;
}