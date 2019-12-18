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
typedef  int /*<<< orphan*/  u32 ;
struct atl2_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATL2_WRITE_REG (struct atl2_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LTSSM_TEST_MODE_DEF ; 
 int /*<<< orphan*/  PCIE_DLL_TX_CTRL1_DEF ; 
 int /*<<< orphan*/  REG_LTSSM_TEST_MODE ; 
 int /*<<< orphan*/  REG_PCIE_DLL_TX_CTRL1 ; 

__attribute__((used)) static void atl2_init_pcie(struct atl2_hw *hw)
{
    u32 value;
    value = LTSSM_TEST_MODE_DEF;
    ATL2_WRITE_REG(hw, REG_LTSSM_TEST_MODE, value);

    value = PCIE_DLL_TX_CTRL1_DEF;
    ATL2_WRITE_REG(hw, REG_PCIE_DLL_TX_CTRL1, value);
}