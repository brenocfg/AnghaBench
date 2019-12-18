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

/* Variables and functions */
 int MAX_DOMAIN_ID ; 
 int /*<<< orphan*/  __clear_bit (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amd_iommu_pd_alloc_bitmap ; 
 int /*<<< orphan*/  pd_bitmap_lock ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void domain_id_free(int id)
{
	spin_lock(&pd_bitmap_lock);
	if (id > 0 && id < MAX_DOMAIN_ID)
		__clear_bit(id, amd_iommu_pd_alloc_bitmap);
	spin_unlock(&pd_bitmap_lock);
}