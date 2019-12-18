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
struct clk {int dummy; } ;
struct TYPE_6__ {struct clk* parent_clk; TYPE_2__* feat; struct clk* dss_clk; TYPE_1__* pdev; } ;
struct TYPE_5__ {scalar_t__ parent_clk_name; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSSERR (char*,...) ; 
 scalar_t__ IS_ERR (struct clk*) ; 
 int PTR_ERR (struct clk*) ; 
 struct clk* clk_get (int /*<<< orphan*/ *,scalar_t__) ; 
 struct clk* devm_clk_get (int /*<<< orphan*/ *,char*) ; 
 TYPE_3__ dss ; 

__attribute__((used)) static int dss_get_clocks(void)
{
	struct clk *clk;

	clk = devm_clk_get(&dss.pdev->dev, "fck");
	if (IS_ERR(clk)) {
		DSSERR("can't get clock fck\n");
		return PTR_ERR(clk);
	}

	dss.dss_clk = clk;

	if (dss.feat->parent_clk_name) {
		clk = clk_get(NULL, dss.feat->parent_clk_name);
		if (IS_ERR(clk)) {
			DSSERR("Failed to get %s\n", dss.feat->parent_clk_name);
			return PTR_ERR(clk);
		}
	} else {
		clk = NULL;
	}

	dss.parent_clk = clk;

	return 0;
}