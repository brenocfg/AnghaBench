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
typedef  int /*<<< orphan*/  u32 ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int of_property_read_u32 (struct device_node const*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*,struct device_node const*,char const*) ; 

__attribute__((used)) static int exynos_dsi_of_read_u32(const struct device_node *np,
				  const char *propname, u32 *out_value)
{
	int ret = of_property_read_u32(np, propname, out_value);

	if (ret < 0)
		pr_err("%pOF: failed to get '%s' property\n", np, propname);

	return ret;
}