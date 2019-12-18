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
struct device_node {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int EFAULT ; 
 int EINVAL ; 
 int ENODEV ; 
 int be32_to_cpup (int /*<<< orphan*/  const*) ; 
 struct device_node* of_find_node_by_phandle (int) ; 
 int /*<<< orphan*/ * of_get_property (struct device_node*,char const*,int*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 int /*<<< orphan*/  of_property_read_u32 (struct device_node*,char const*,int*) ; 
 int /*<<< orphan*/  pr_debug (char*,struct device_node*,char const*,int,int,int,int,int,int) ; 
 int /*<<< orphan*/  pr_err (char*,struct device_node*,char const*,...) ; 
 int /*<<< orphan*/  pr_info (char*,struct device_node*,char const*,int,struct device_node*) ; 

int of_map_rid(struct device_node *np, u32 rid,
	       const char *map_name, const char *map_mask_name,
	       struct device_node **target, u32 *id_out)
{
	u32 map_mask, masked_rid;
	int map_len;
	const __be32 *map = NULL;

	if (!np || !map_name || (!target && !id_out))
		return -EINVAL;

	map = of_get_property(np, map_name, &map_len);
	if (!map) {
		if (target)
			return -ENODEV;
		/* Otherwise, no map implies no translation */
		*id_out = rid;
		return 0;
	}

	if (!map_len || map_len % (4 * sizeof(*map))) {
		pr_err("%pOF: Error: Bad %s length: %d\n", np,
			map_name, map_len);
		return -EINVAL;
	}

	/* The default is to select all bits. */
	map_mask = 0xffffffff;

	/*
	 * Can be overridden by "{iommu,msi}-map-mask" property.
	 * If of_property_read_u32() fails, the default is used.
	 */
	if (map_mask_name)
		of_property_read_u32(np, map_mask_name, &map_mask);

	masked_rid = map_mask & rid;
	for ( ; map_len > 0; map_len -= 4 * sizeof(*map), map += 4) {
		struct device_node *phandle_node;
		u32 rid_base = be32_to_cpup(map + 0);
		u32 phandle = be32_to_cpup(map + 1);
		u32 out_base = be32_to_cpup(map + 2);
		u32 rid_len = be32_to_cpup(map + 3);

		if (rid_base & ~map_mask) {
			pr_err("%pOF: Invalid %s translation - %s-mask (0x%x) ignores rid-base (0x%x)\n",
				np, map_name, map_name,
				map_mask, rid_base);
			return -EFAULT;
		}

		if (masked_rid < rid_base || masked_rid >= rid_base + rid_len)
			continue;

		phandle_node = of_find_node_by_phandle(phandle);
		if (!phandle_node)
			return -ENODEV;

		if (target) {
			if (*target)
				of_node_put(phandle_node);
			else
				*target = phandle_node;

			if (*target != phandle_node)
				continue;
		}

		if (id_out)
			*id_out = masked_rid - rid_base + out_base;

		pr_debug("%pOF: %s, using mask %08x, rid-base: %08x, out-base: %08x, length: %08x, rid: %08x -> %08x\n",
			np, map_name, map_mask, rid_base, out_base,
			rid_len, rid, masked_rid - rid_base + out_base);
		return 0;
	}

	pr_info("%pOF: no %s translation for rid 0x%x on %pOF\n", np, map_name,
		rid, target && *target ? *target : NULL);

	/* Bypasses translation */
	if (id_out)
		*id_out = rid;
	return 0;
}