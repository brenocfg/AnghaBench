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
struct be_pcie_res_desc {int sriov_state; int pf_state; int pf_type; int num_vfs; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct be_pcie_res_desc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void be_reset_pcie_desc(struct be_pcie_res_desc *pcie)
{
	memset(pcie, 0, sizeof(*pcie));
	pcie->sriov_state = 0xFF;
	pcie->pf_state = 0xFF;
	pcie->pf_type = 0xFF;
	pcie->num_vfs = 0xFFFF;
}