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
struct intel_lpss {int /*<<< orphan*/  priv; } ;
struct clk {int dummy; } ;
typedef  int /*<<< orphan*/  name ;

/* Variables and functions */
 int /*<<< orphan*/  CLK_SET_RATE_PARENT ; 
 scalar_t__ IS_ERR (struct clk*) ; 
 int PTR_ERR (struct clk*) ; 
 int /*<<< orphan*/  __clk_get_name (struct clk*) ; 
 struct clk* clk_register_fractional_divider (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct clk* clk_register_gate (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*) ; 

__attribute__((used)) static int intel_lpss_register_clock_divider(struct intel_lpss *lpss,
					     const char *devname,
					     struct clk **clk)
{
	char name[32];
	struct clk *tmp = *clk;

	snprintf(name, sizeof(name), "%s-enable", devname);
	tmp = clk_register_gate(NULL, name, __clk_get_name(tmp), 0,
				lpss->priv, 0, 0, NULL);
	if (IS_ERR(tmp))
		return PTR_ERR(tmp);

	snprintf(name, sizeof(name), "%s-div", devname);
	tmp = clk_register_fractional_divider(NULL, name, __clk_get_name(tmp),
					      0, lpss->priv, 1, 15, 16, 15, 0,
					      NULL);
	if (IS_ERR(tmp))
		return PTR_ERR(tmp);
	*clk = tmp;

	snprintf(name, sizeof(name), "%s-update", devname);
	tmp = clk_register_gate(NULL, name, __clk_get_name(tmp),
				CLK_SET_RATE_PARENT, lpss->priv, 31, 0, NULL);
	if (IS_ERR(tmp))
		return PTR_ERR(tmp);
	*clk = tmp;

	return 0;
}