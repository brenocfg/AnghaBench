#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct dra7_atl_desc {int enabled; TYPE_1__* cinfo; int /*<<< orphan*/  id; int /*<<< orphan*/  probed; } ;
struct clk_hw {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRA7_ATL_SWEN_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atl_write (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_sync (int /*<<< orphan*/ ) ; 
 struct dra7_atl_desc* to_atl_desc (struct clk_hw*) ; 

__attribute__((used)) static void atl_clk_disable(struct clk_hw *hw)
{
	struct dra7_atl_desc *cdesc = to_atl_desc(hw);

	if (!cdesc->probed)
		goto out;

	atl_write(cdesc->cinfo, DRA7_ATL_SWEN_REG(cdesc->id), 0);
	pm_runtime_put_sync(cdesc->cinfo->dev);

out:
	cdesc->enabled = false;
}