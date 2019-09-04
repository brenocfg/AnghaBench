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
typedef  int /*<<< orphan*/  phys_addr_t ;
typedef  int __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int cpu_to_be32 (int) ; 
 struct device_node* of_find_node_by_name (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  of_translate_address (struct device_node*,int*) ; 

__attribute__((used)) static phys_addr_t mvebu_internal_reg_base(void)
{
	struct device_node *np;
	__be32 in_addr[2];

	np = of_find_node_by_name(NULL, "internal-regs");
	BUG_ON(!np);

	/*
	 * Ask the DT what is the internal register address on this
	 * platform. In the mvebu-mbus DT binding, 0xf0010000
	 * corresponds to the internal register window.
	 */
	in_addr[0] = cpu_to_be32(0xf0010000);
	in_addr[1] = 0x0;

	return of_translate_address(np, in_addr);
}