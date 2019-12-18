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
struct clk_mapping {scalar_t__ phys; scalar_t__ base; int /*<<< orphan*/  ref; int /*<<< orphan*/  len; } ;
struct clk {struct clk_mapping* mapping; scalar_t__ enable_reg; scalar_t__ mapped_reg; int /*<<< orphan*/  parent; } ;
typedef  scalar_t__ phys_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int ENXIO ; 
 struct clk_mapping dummy_mapping ; 
 scalar_t__ ioremap_nocache (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kref_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 struct clk* lookup_root_clock (struct clk*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int clk_establish_mapping(struct clk *clk)
{
	struct clk_mapping *mapping = clk->mapping;

	/*
	 * Propagate mappings.
	 */
	if (!mapping) {
		struct clk *clkp;

		/*
		 * dummy mapping for root clocks with no specified ranges
		 */
		if (!clk->parent) {
			clk->mapping = &dummy_mapping;
			goto out;
		}

		/*
		 * If we're on a child clock and it provides no mapping of its
		 * own, inherit the mapping from its root clock.
		 */
		clkp = lookup_root_clock(clk);
		mapping = clkp->mapping;
		BUG_ON(!mapping);
	}

	/*
	 * Establish initial mapping.
	 */
	if (!mapping->base && mapping->phys) {
		kref_init(&mapping->ref);

		mapping->base = ioremap_nocache(mapping->phys, mapping->len);
		if (unlikely(!mapping->base))
			return -ENXIO;
	} else if (mapping->base) {
		/*
		 * Bump the refcount for an existing mapping
		 */
		kref_get(&mapping->ref);
	}

	clk->mapping = mapping;
out:
	clk->mapped_reg = clk->mapping->base;
	clk->mapped_reg += (phys_addr_t)clk->enable_reg - clk->mapping->phys;
	return 0;
}