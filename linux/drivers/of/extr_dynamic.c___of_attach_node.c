#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct device_node {char* name; TYPE_1__* parent; struct device_node* sibling; int /*<<< orphan*/ * child; int /*<<< orphan*/  phandle; } ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_2__ {struct device_node* child; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_PPC_PSERIES ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OF_DETACHED ; 
 int /*<<< orphan*/  OF_OVERLAY ; 
 void* __of_get_property (struct device_node*,char*,int*) ; 
 int /*<<< orphan*/  be32_to_cpup (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  of_node_check_flag (struct device_node*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_node_clear_flag (struct device_node*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __of_attach_node(struct device_node *np)
{
	const __be32 *phandle;
	int sz;

	if (!of_node_check_flag(np, OF_OVERLAY)) {
		np->name = __of_get_property(np, "name", NULL);
		if (!np->name)
			np->name = "<NULL>";

		phandle = __of_get_property(np, "phandle", &sz);
		if (!phandle)
			phandle = __of_get_property(np, "linux,phandle", &sz);
		if (IS_ENABLED(CONFIG_PPC_PSERIES) && !phandle)
			phandle = __of_get_property(np, "ibm,phandle", &sz);
		if (phandle && (sz >= 4))
			np->phandle = be32_to_cpup(phandle);
		else
			np->phandle = 0;
	}

	np->child = NULL;
	np->sibling = np->parent->child;
	np->parent->child = np;
	of_node_clear_flag(np, OF_DETACHED);
}