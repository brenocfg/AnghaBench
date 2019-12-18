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
struct clk_mapping {int /*<<< orphan*/  ref; } ;
struct clk {int /*<<< orphan*/ * mapped_reg; struct clk_mapping* mapping; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_destroy_mapping ; 
 struct clk_mapping dummy_mapping ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void clk_teardown_mapping(struct clk *clk)
{
	struct clk_mapping *mapping = clk->mapping;

	/* Nothing to do */
	if (mapping == &dummy_mapping)
		goto out;

	kref_put(&mapping->ref, clk_destroy_mapping);
	clk->mapping = NULL;
out:
	clk->mapped_reg = NULL;
}