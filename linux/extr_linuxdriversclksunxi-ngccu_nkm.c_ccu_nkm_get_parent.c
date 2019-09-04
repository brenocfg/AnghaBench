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
typedef  int /*<<< orphan*/  u8 ;
struct clk_hw {int dummy; } ;
struct ccu_nkm {int /*<<< orphan*/  mux; int /*<<< orphan*/  common; } ;

/* Variables and functions */
 int /*<<< orphan*/  ccu_mux_helper_get_parent (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct ccu_nkm* hw_to_ccu_nkm (struct clk_hw*) ; 

__attribute__((used)) static u8 ccu_nkm_get_parent(struct clk_hw *hw)
{
	struct ccu_nkm *nkm = hw_to_ccu_nkm(hw);

	return ccu_mux_helper_get_parent(&nkm->common, &nkm->mux);
}