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
struct omap_iommu {int dummy; } ;
struct iotlb_lock {int vict; } ;
struct cr_regs {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  iotlb_lock_get (struct omap_iommu*,struct iotlb_lock*) ; 
 int /*<<< orphan*/  iotlb_lock_set (struct omap_iommu*,struct iotlb_lock*) ; 
 int /*<<< orphan*/  iotlb_read_cr (struct omap_iommu*,struct cr_regs*) ; 

struct cr_regs __iotlb_read_cr(struct omap_iommu *obj, int n)
{
	struct cr_regs cr;
	struct iotlb_lock l;

	iotlb_lock_get(obj, &l);
	l.vict = n;
	iotlb_lock_set(obj, &l);
	iotlb_read_cr(obj, &cr);

	return cr;
}