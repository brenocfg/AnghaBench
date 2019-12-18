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
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int pinctrl_get_list_and_count (struct device_node const*,char const*,int /*<<< orphan*/  const**,int*,int*) ; 

int pinctrl_count_index_with_args(const struct device_node *np,
				  const char *list_name)
{
	const __be32 *list;
	int size, nr_cells, error;

	error = pinctrl_get_list_and_count(np, list_name, &list,
					   &nr_cells, &size);
	if (error)
		return error;

	return size;
}