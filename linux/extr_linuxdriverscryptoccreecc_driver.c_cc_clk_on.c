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
struct clk {int dummy; } ;
struct cc_drvdata {struct clk* clk; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct clk*) ; 
 int clk_prepare_enable (struct clk*) ; 

int cc_clk_on(struct cc_drvdata *drvdata)
{
	struct clk *clk = drvdata->clk;
	int rc;

	if (IS_ERR(clk))
		/* Not all devices have a clock associated with CCREE  */
		return 0;

	rc = clk_prepare_enable(clk);
	if (rc)
		return rc;

	return 0;
}