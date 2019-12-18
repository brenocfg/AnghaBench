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
struct i40e_hw {int dummy; } ;
struct i40e_pf {int /*<<< orphan*/  pfr_count; TYPE_1__* pdev; struct i40e_hw hw; } ;
typedef  int /*<<< orphan*/  i40e_status ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i40e_pf_reset (struct i40e_hw*) ; 
 int /*<<< orphan*/  msleep (unsigned short const) ; 

__attribute__((used)) static i40e_status i40e_pf_loop_reset(struct i40e_pf *pf)
{
	const unsigned short MAX_CNT = 1000;
	const unsigned short MSECS = 10;
	struct i40e_hw *hw = &pf->hw;
	i40e_status ret;
	int cnt;

	for (cnt = 0; cnt < MAX_CNT; ++cnt) {
		ret = i40e_pf_reset(hw);
		if (!ret)
			break;
		msleep(MSECS);
	}

	if (cnt == MAX_CNT) {
		dev_info(&pf->pdev->dev, "PF reset failed: %d\n", ret);
		return ret;
	}

	pf->pfr_count++;
	return ret;
}