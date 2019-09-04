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
struct device_node {struct cbe_regs_map* data; struct device_node* parent; int /*<<< orphan*/  type; } ;
struct cbe_regs_map {struct device_node* be_node; struct device_node* cpu_node; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int cbe_regs_map_count ; 
 struct cbe_regs_map* cbe_regs_maps ; 
 scalar_t__ strcasecmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static struct cbe_regs_map *cbe_find_map(struct device_node *np)
{
	int i;
	struct device_node *tmp_np;

	if (strcasecmp(np->type, "spe")) {
		for (i = 0; i < cbe_regs_map_count; i++)
			if (cbe_regs_maps[i].cpu_node == np ||
			    cbe_regs_maps[i].be_node == np)
				return &cbe_regs_maps[i];
		return NULL;
	}

	if (np->data)
		return np->data;

	/* walk up path until cpu or be node was found */
	tmp_np = np;
	do {
		tmp_np = tmp_np->parent;
		/* on a correct devicetree we wont get up to root */
		BUG_ON(!tmp_np);
	} while (strcasecmp(tmp_np->type, "cpu") &&
		 strcasecmp(tmp_np->type, "be"));

	np->data = cbe_find_map(tmp_np);

	return np->data;
}