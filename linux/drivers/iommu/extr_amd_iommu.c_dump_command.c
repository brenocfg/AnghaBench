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
struct iommu_cmd {int /*<<< orphan*/ * data; } ;

/* Variables and functions */
 struct iommu_cmd* iommu_phys_to_virt (unsigned long) ; 
 int /*<<< orphan*/  pr_err (char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dump_command(unsigned long phys_addr)
{
	struct iommu_cmd *cmd = iommu_phys_to_virt(phys_addr);
	int i;

	for (i = 0; i < 4; ++i)
		pr_err("CMD[%d]: %08x\n", i, cmd->data[i]);
}