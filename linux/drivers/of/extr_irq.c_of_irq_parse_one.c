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
typedef  int u32 ;
struct of_phandle_args {int args_count; int /*<<< orphan*/ * args; struct device_node* np; } ;
struct device_node {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int EINVAL ; 
 int OF_IMAP_OLDWORLD_MAC ; 
 int /*<<< orphan*/ * of_get_property (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 struct device_node* of_irq_find_parent (struct device_node*) ; 
 int of_irq_parse_oldworld (struct device_node*,int,struct of_phandle_args*) ; 
 int of_irq_parse_raw (int /*<<< orphan*/  const*,struct of_phandle_args*) ; 
 int of_irq_workarounds ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 int of_parse_phandle_with_args (struct device_node*,char*,char*,int,struct of_phandle_args*) ; 
 scalar_t__ of_property_read_u32 (struct device_node*,char*,int*) ; 
 int of_property_read_u32_index (struct device_node*,char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,...) ; 

int of_irq_parse_one(struct device_node *device, int index, struct of_phandle_args *out_irq)
{
	struct device_node *p;
	const __be32 *addr;
	u32 intsize;
	int i, res;

	pr_debug("of_irq_parse_one: dev=%pOF, index=%d\n", device, index);

	/* OldWorld mac stuff is "special", handle out of line */
	if (of_irq_workarounds & OF_IMAP_OLDWORLD_MAC)
		return of_irq_parse_oldworld(device, index, out_irq);

	/* Get the reg property (if any) */
	addr = of_get_property(device, "reg", NULL);

	/* Try the new-style interrupts-extended first */
	res = of_parse_phandle_with_args(device, "interrupts-extended",
					"#interrupt-cells", index, out_irq);
	if (!res)
		return of_irq_parse_raw(addr, out_irq);

	/* Look for the interrupt parent. */
	p = of_irq_find_parent(device);
	if (p == NULL)
		return -EINVAL;

	/* Get size of interrupt specifier */
	if (of_property_read_u32(p, "#interrupt-cells", &intsize)) {
		res = -EINVAL;
		goto out;
	}

	pr_debug(" parent=%pOF, intsize=%d\n", p, intsize);

	/* Copy intspec into irq structure */
	out_irq->np = p;
	out_irq->args_count = intsize;
	for (i = 0; i < intsize; i++) {
		res = of_property_read_u32_index(device, "interrupts",
						 (index * intsize) + i,
						 out_irq->args + i);
		if (res)
			goto out;
	}

	pr_debug(" intspec=%d\n", *out_irq->args);


	/* Check if there are any interrupt-map translations to process */
	res = of_irq_parse_raw(addr, out_irq);
 out:
	of_node_put(p);
	return res;
}