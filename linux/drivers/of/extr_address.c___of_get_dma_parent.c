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
struct of_phandle_args {int /*<<< orphan*/  np; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 struct device_node* of_get_parent (struct device_node const*) ; 
 struct device_node* of_node_get (int /*<<< orphan*/ ) ; 
 int of_parse_phandle_with_args (struct device_node const*,char*,char*,int,struct of_phandle_args*) ; 
 int of_property_match_string (struct device_node const*,char*,char*) ; 

__attribute__((used)) static struct device_node *__of_get_dma_parent(const struct device_node *np)
{
	struct of_phandle_args args;
	int ret, index;

	index = of_property_match_string(np, "interconnect-names", "dma-mem");
	if (index < 0)
		return of_get_parent(np);

	ret = of_parse_phandle_with_args(np, "interconnects",
					 "#interconnect-cells",
					 index, &args);
	if (ret < 0)
		return of_get_parent(np);

	return of_node_get(args.np);
}