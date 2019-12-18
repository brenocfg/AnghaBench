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
struct fdt_header {int dummy; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ fdt_check_header (void const*) ; 
 int fdt_totalsize (void const*) ; 
 int /*<<< orphan*/  kfree (void const*) ; 
 void* kmemdup (void const*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_fdt_unflatten_tree (void const*,int /*<<< orphan*/ *,struct device_node**) ; 
 int of_overlay_apply (void const*,struct device_node*,int*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

int of_overlay_fdt_apply(const void *overlay_fdt, u32 overlay_fdt_size,
			 int *ovcs_id)
{
	const void *new_fdt;
	int ret;
	u32 size;
	struct device_node *overlay_root;

	*ovcs_id = 0;
	ret = 0;

	if (overlay_fdt_size < sizeof(struct fdt_header) ||
	    fdt_check_header(overlay_fdt)) {
		pr_err("Invalid overlay_fdt header\n");
		return -EINVAL;
	}

	size = fdt_totalsize(overlay_fdt);
	if (overlay_fdt_size < size)
		return -EINVAL;

	/*
	 * Must create permanent copy of FDT because of_fdt_unflatten_tree()
	 * will create pointers to the passed in FDT in the unflattened tree.
	 */
	new_fdt = kmemdup(overlay_fdt, size, GFP_KERNEL);
	if (!new_fdt)
		return -ENOMEM;

	of_fdt_unflatten_tree(new_fdt, NULL, &overlay_root);
	if (!overlay_root) {
		pr_err("unable to unflatten overlay_fdt\n");
		ret = -EINVAL;
		goto out_free_new_fdt;
	}

	ret = of_overlay_apply(new_fdt, overlay_root, ovcs_id);
	if (ret < 0) {
		/*
		 * new_fdt and overlay_root now belong to the overlay
		 * changeset.
		 * overlay changeset code is responsible for freeing them.
		 */
		goto out;
	}

	return 0;


out_free_new_fdt:
	kfree(new_fdt);

out:
	return ret;
}