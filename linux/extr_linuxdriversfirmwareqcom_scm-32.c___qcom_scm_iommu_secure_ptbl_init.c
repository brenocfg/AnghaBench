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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct device {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 

int __qcom_scm_iommu_secure_ptbl_init(struct device *dev, u64 addr, u32 size,
				      u32 spare)
{
	return -ENODEV;
}