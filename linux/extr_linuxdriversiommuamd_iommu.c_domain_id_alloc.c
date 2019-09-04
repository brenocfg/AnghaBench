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
typedef  int u16 ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int MAX_DOMAIN_ID ; 
 int /*<<< orphan*/  __set_bit (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amd_iommu_pd_alloc_bitmap ; 
 int find_first_zero_bit (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pd_bitmap_lock ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static u16 domain_id_alloc(void)
{
	int id;

	spin_lock(&pd_bitmap_lock);
	id = find_first_zero_bit(amd_iommu_pd_alloc_bitmap, MAX_DOMAIN_ID);
	BUG_ON(id == 0);
	if (id > 0 && id < MAX_DOMAIN_ID)
		__set_bit(id, amd_iommu_pd_alloc_bitmap);
	else
		id = 0;
	spin_unlock(&pd_bitmap_lock);

	return id;
}