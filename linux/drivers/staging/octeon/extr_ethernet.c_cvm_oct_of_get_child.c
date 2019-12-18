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
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int be32_to_cpu (int /*<<< orphan*/  const) ; 
 struct device_node* of_get_next_child (struct device_node const*,struct device_node*) ; 
 int /*<<< orphan*/ * of_get_property (struct device_node*,char*,int*) ; 

__attribute__((used)) static struct device_node *cvm_oct_of_get_child
				(const struct device_node *parent, int reg_val)
{
	struct device_node *node = NULL;
	int size;
	const __be32 *addr;

	for (;;) {
		node = of_get_next_child(parent, node);
		if (!node)
			break;
		addr = of_get_property(node, "reg", &size);
		if (addr && (be32_to_cpu(*addr) == reg_val))
			break;
	}
	return node;
}