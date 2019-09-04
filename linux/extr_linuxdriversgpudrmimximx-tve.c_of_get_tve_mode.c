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
struct device_node {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int const EINVAL ; 
 int /*<<< orphan*/ * imx_tve_modes ; 
 int of_property_read_string (struct device_node*,char*,char const**) ; 
 int /*<<< orphan*/  strcasecmp (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static const int of_get_tve_mode(struct device_node *np)
{
	const char *bm;
	int ret, i;

	ret = of_property_read_string(np, "fsl,tve-mode", &bm);
	if (ret < 0)
		return ret;

	for (i = 0; i < ARRAY_SIZE(imx_tve_modes); i++)
		if (!strcasecmp(bm, imx_tve_modes[i]))
			return i;

	return -EINVAL;
}