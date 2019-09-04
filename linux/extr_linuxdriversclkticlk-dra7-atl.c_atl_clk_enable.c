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
struct dra7_atl_desc {int enabled; int /*<<< orphan*/  id; TYPE_1__* cinfo; scalar_t__ divider; int /*<<< orphan*/  valid; int /*<<< orphan*/  probed; } ;
struct clk_hw {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRA7_ATL_ATLCR_REG (int /*<<< orphan*/ ) ; 
 scalar_t__ DRA7_ATL_SWEN ; 
 int /*<<< orphan*/  DRA7_ATL_SWEN_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atl_write (TYPE_1__*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 struct dra7_atl_desc* to_atl_desc (struct clk_hw*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int atl_clk_enable(struct clk_hw *hw)
{
	struct dra7_atl_desc *cdesc = to_atl_desc(hw);

	if (!cdesc->probed)
		goto out;

	if (unlikely(!cdesc->valid))
		dev_warn(cdesc->cinfo->dev, "atl%d has not been configured\n",
			 cdesc->id);
	pm_runtime_get_sync(cdesc->cinfo->dev);

	atl_write(cdesc->cinfo, DRA7_ATL_ATLCR_REG(cdesc->id),
		  cdesc->divider - 1);
	atl_write(cdesc->cinfo, DRA7_ATL_SWEN_REG(cdesc->id), DRA7_ATL_SWEN);

out:
	cdesc->enabled = true;

	return 0;
}