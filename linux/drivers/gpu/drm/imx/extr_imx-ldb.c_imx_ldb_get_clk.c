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
struct imx_ldb {void** clk_pll; int /*<<< orphan*/  dev; void** clk; } ;
typedef  int /*<<< orphan*/  clkname ;

/* Variables and functions */
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 int PTR_ERR_OR_ZERO (void*) ; 
 void* devm_clk_get (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 

__attribute__((used)) static int imx_ldb_get_clk(struct imx_ldb *ldb, int chno)
{
	char clkname[16];

	snprintf(clkname, sizeof(clkname), "di%d", chno);
	ldb->clk[chno] = devm_clk_get(ldb->dev, clkname);
	if (IS_ERR(ldb->clk[chno]))
		return PTR_ERR(ldb->clk[chno]);

	snprintf(clkname, sizeof(clkname), "di%d_pll", chno);
	ldb->clk_pll[chno] = devm_clk_get(ldb->dev, clkname);

	return PTR_ERR_OR_ZERO(ldb->clk_pll[chno]);
}