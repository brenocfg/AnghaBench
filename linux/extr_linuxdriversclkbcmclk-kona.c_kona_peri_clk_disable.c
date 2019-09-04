#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  name; } ;
struct TYPE_5__ {TYPE_1__* peri; } ;
struct kona_clk {TYPE_3__ init_data; int /*<<< orphan*/  ccu; TYPE_2__ u; } ;
struct clk_hw {int dummy; } ;
struct bcm_clk_gate {int dummy; } ;
struct TYPE_4__ {struct bcm_clk_gate gate; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_gate (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct bcm_clk_gate*,int) ; 
 struct kona_clk* to_kona_clk (struct clk_hw*) ; 

__attribute__((used)) static void kona_peri_clk_disable(struct clk_hw *hw)
{
	struct kona_clk *bcm_clk = to_kona_clk(hw);
	struct bcm_clk_gate *gate = &bcm_clk->u.peri->gate;

	(void)clk_gate(bcm_clk->ccu, bcm_clk->init_data.name, gate, false);
}