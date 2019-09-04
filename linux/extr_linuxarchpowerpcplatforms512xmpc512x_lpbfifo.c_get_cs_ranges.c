#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct device_node {int dummy; } ;
struct device {int dummy; } ;
struct cs_range {int dummy; } ;
struct TYPE_4__ {scalar_t__ base; } ;
struct TYPE_3__ {int cs_n; TYPE_2__* cs_ranges; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 TYPE_2__* devm_kcalloc (struct device*,int,int,int /*<<< orphan*/ ) ; 
 TYPE_1__ lpbfifo ; 
 struct device_node* of_find_compatible_node (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int* of_get_property (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 int of_property_count_u32_elems (struct device_node*,char*) ; 
 scalar_t__ of_property_read_u32_array (struct device_node*,char*,int*,int) ; 

__attribute__((used)) static int get_cs_ranges(struct device *dev)
{
	int ret = -ENODEV;
	struct device_node *lb_node;
	const u32 *addr_cells_p;
	const u32 *size_cells_p;
	int proplen;
	size_t i;

	lb_node = of_find_compatible_node(NULL, NULL, "fsl,mpc5121-localbus");
	if (!lb_node)
		return ret;

	/*
	 * The node defined as compatible with 'fsl,mpc5121-localbus'
	 * should have two address cells and one size cell.
	 * Every item of its ranges property should consist of:
	 * - the first address cell which is the chipselect number;
	 * - the second address cell which is the offset in the chipselect,
	 *    must be zero.
	 * - CPU address of the beginning of an access window;
	 * - the only size cell which is the size of an access window.
	 */
	addr_cells_p = of_get_property(lb_node, "#address-cells", NULL);
	size_cells_p = of_get_property(lb_node, "#size-cells", NULL);
	if (addr_cells_p == NULL || *addr_cells_p != 2 ||
				size_cells_p == NULL ||	*size_cells_p != 1) {
		goto end;
	}

	proplen = of_property_count_u32_elems(lb_node, "ranges");
	if (proplen <= 0 || proplen % 4 != 0)
		goto end;

	lpbfifo.cs_n = proplen / 4;
	lpbfifo.cs_ranges = devm_kcalloc(dev, lpbfifo.cs_n,
					sizeof(struct cs_range), GFP_KERNEL);
	if (!lpbfifo.cs_ranges)
		goto end;

	if (of_property_read_u32_array(lb_node, "ranges",
				(u32 *)lpbfifo.cs_ranges, proplen) != 0) {
		goto end;
	}

	for (i = 0; i < lpbfifo.cs_n; i++) {
		if (lpbfifo.cs_ranges[i].base != 0)
			goto end;
	}

	ret = 0;

 end:
	of_node_put(lb_node);
	return ret;
}