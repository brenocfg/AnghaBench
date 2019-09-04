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
struct rockchip_ddrclk {int /*<<< orphan*/  lock; } ;
struct clk_hw {int dummy; } ;
struct arm_smccc_res {int a0; } ;

/* Variables and functions */
 int /*<<< orphan*/  ROCKCHIP_SIP_CONFIG_DRAM_SET_RATE ; 
 int /*<<< orphan*/  ROCKCHIP_SIP_DRAM_FREQ ; 
 int /*<<< orphan*/  arm_smccc_smc (int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct arm_smccc_res*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 
 struct rockchip_ddrclk* to_rockchip_ddrclk_hw (struct clk_hw*) ; 

__attribute__((used)) static int rockchip_ddrclk_sip_set_rate(struct clk_hw *hw, unsigned long drate,
					unsigned long prate)
{
	struct rockchip_ddrclk *ddrclk = to_rockchip_ddrclk_hw(hw);
	unsigned long flags;
	struct arm_smccc_res res;

	spin_lock_irqsave(ddrclk->lock, flags);
	arm_smccc_smc(ROCKCHIP_SIP_DRAM_FREQ, drate, 0,
		      ROCKCHIP_SIP_CONFIG_DRAM_SET_RATE,
		      0, 0, 0, 0, &res);
	spin_unlock_irqrestore(ddrclk->lock, flags);

	return res.a0;
}