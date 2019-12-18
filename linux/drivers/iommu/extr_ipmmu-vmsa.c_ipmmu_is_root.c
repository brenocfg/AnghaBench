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
struct ipmmu_vmsa_device {struct ipmmu_vmsa_device* root; } ;

/* Variables and functions */

__attribute__((used)) static bool ipmmu_is_root(struct ipmmu_vmsa_device *mmu)
{
	return mmu->root == mmu;
}