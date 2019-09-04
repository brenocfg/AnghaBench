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
struct hinic_hwif {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HINIC_PCIE_AT_DISABLE ; 
 int /*<<< orphan*/  HINIC_PCIE_PH_DISABLE ; 
 int /*<<< orphan*/  HINIC_PCIE_SNOOP ; 
 int /*<<< orphan*/  HINIC_PCIE_ST_DISABLE ; 
 int /*<<< orphan*/  HINIC_PCIE_TPH_DISABLE ; 
 int /*<<< orphan*/  PCIE_ATTR_ENTRY ; 
 int /*<<< orphan*/  set_dma_attr (struct hinic_hwif*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dma_attr_init(struct hinic_hwif *hwif)
{
	set_dma_attr(hwif, PCIE_ATTR_ENTRY, HINIC_PCIE_ST_DISABLE,
		     HINIC_PCIE_AT_DISABLE, HINIC_PCIE_PH_DISABLE,
		     HINIC_PCIE_SNOOP, HINIC_PCIE_TPH_DISABLE);
}