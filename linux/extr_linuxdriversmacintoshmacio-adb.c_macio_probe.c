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
 int ENODEV ; 
 struct device_node* of_find_compatible_node (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 

int macio_probe(void)
{
	struct device_node *np;

	np = of_find_compatible_node(NULL, "adb", "chrp,adb0");
	if (np) {
		of_node_put(np);
		return 0;
	}
	return -ENODEV;
}