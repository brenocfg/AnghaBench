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
struct cpc925_mc_pdata {unsigned long total_mem; } ;

/* Variables and functions */
 int /*<<< orphan*/  edac_dbg (int,char*,unsigned long,...) ; 
 struct device_node* of_find_node_by_type (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ of_get_property (struct device_node*,char*,int*) ; 
 int of_n_addr_cells (struct device_node*) ; 
 int of_n_size_cells (struct device_node*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 unsigned long of_read_number (unsigned int const*,int) ; 

__attribute__((used)) static void get_total_mem(struct cpc925_mc_pdata *pdata)
{
	struct device_node *np = NULL;
	const unsigned int *reg, *reg_end;
	int len, sw, aw;
	unsigned long start, size;

	np = of_find_node_by_type(NULL, "memory");
	if (!np)
		return;

	aw = of_n_addr_cells(np);
	sw = of_n_size_cells(np);
	reg = (const unsigned int *)of_get_property(np, "reg", &len);
	reg_end = reg + len/4;

	pdata->total_mem = 0;
	do {
		start = of_read_number(reg, aw);
		reg += aw;
		size = of_read_number(reg, sw);
		reg += sw;
		edac_dbg(1, "start 0x%lx, size 0x%lx\n", start, size);
		pdata->total_mem += size;
	} while (reg < reg_end);

	of_node_put(np);
	edac_dbg(0, "total_mem 0x%lx\n", pdata->total_mem);
}