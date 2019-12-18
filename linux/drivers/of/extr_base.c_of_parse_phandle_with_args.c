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
struct of_phandle_args {int dummy; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int __of_parse_phandle_with_args (struct device_node const*,char const*,char const*,int,int,struct of_phandle_args*) ; 

int of_parse_phandle_with_args(const struct device_node *np, const char *list_name,
				const char *cells_name, int index,
				struct of_phandle_args *out_args)
{
	int cell_count = -1;

	if (index < 0)
		return -EINVAL;

	/* If cells_name is NULL we assume a cell count of 0 */
	if (!cells_name)
		cell_count = 0;

	return __of_parse_phandle_with_args(np, list_name, cells_name,
					    cell_count, index, out_args);
}