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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct clk {int dummy; } ;
typedef  int /*<<< orphan*/  name2 ;

/* Variables and functions */
 int /*<<< orphan*/  EPROBE_DEFER ; 
 int /*<<< orphan*/  IS_ERR (struct clk*) ; 
 int /*<<< orphan*/  PTR_ERR (struct clk*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,char const*,char*) ; 
 struct clk* devm_clk_get (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*) ; 

struct clk *msm_clk_get(struct platform_device *pdev, const char *name)
{
	struct clk *clk;
	char name2[32];

	clk = devm_clk_get(&pdev->dev, name);
	if (!IS_ERR(clk) || PTR_ERR(clk) == -EPROBE_DEFER)
		return clk;

	snprintf(name2, sizeof(name2), "%s_clk", name);

	clk = devm_clk_get(&pdev->dev, name2);
	if (!IS_ERR(clk))
		dev_warn(&pdev->dev, "Using legacy clk name binding.  Use "
				"\"%s\" instead of \"%s\"\n", name, name2);

	return clk;
}