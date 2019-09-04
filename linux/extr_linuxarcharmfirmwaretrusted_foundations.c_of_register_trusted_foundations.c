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
struct trusted_foundations_platform_data {int /*<<< orphan*/  version_minor; int /*<<< orphan*/  version_major; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 struct device_node* of_find_compatible_node (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int of_property_read_u32 (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  register_trusted_foundations (struct trusted_foundations_platform_data*) ; 

void of_register_trusted_foundations(void)
{
	struct device_node *node;
	struct trusted_foundations_platform_data pdata;
	int err;

	node = of_find_compatible_node(NULL, NULL, "tlm,trusted-foundations");
	if (!node)
		return;

	err = of_property_read_u32(node, "tlm,version-major",
				   &pdata.version_major);
	if (err != 0)
		panic("Trusted Foundation: missing version-major property\n");
	err = of_property_read_u32(node, "tlm,version-minor",
				   &pdata.version_minor);
	if (err != 0)
		panic("Trusted Foundation: missing version-minor property\n");
	register_trusted_foundations(&pdata);
}