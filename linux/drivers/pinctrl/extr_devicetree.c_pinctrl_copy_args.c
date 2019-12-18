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
struct of_phandle_args {int args_count; int /*<<< orphan*/ * args; struct device_node* np; } ;
struct device_node {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  be32_to_cpup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct of_phandle_args*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int pinctrl_copy_args(const struct device_node *np,
			     const __be32 *list,
			     int index, int nr_cells, int nr_elem,
			     struct of_phandle_args *out_args)
{
	int i;

	memset(out_args, 0, sizeof(*out_args));
	out_args->np = (struct device_node *)np;
	out_args->args_count = nr_cells + 1;

	if (index >= nr_elem)
		return -EINVAL;

	list += index * (nr_cells + 1);

	for (i = 0; i < nr_cells + 1; i++)
		out_args->args[i] = be32_to_cpup(list++);

	return 0;
}