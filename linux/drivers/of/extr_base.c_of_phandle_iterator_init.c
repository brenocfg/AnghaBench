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
struct of_phandle_iterator {char const* cells_name; int cell_count; int /*<<< orphan*/  const* cur; int /*<<< orphan*/  const* phandle_end; int /*<<< orphan*/  const* list_end; struct device_node const* parent; } ;
struct device_node {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 int /*<<< orphan*/  memset (struct of_phandle_iterator*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * of_get_property (struct device_node const*,char const*,int*) ; 

int of_phandle_iterator_init(struct of_phandle_iterator *it,
		const struct device_node *np,
		const char *list_name,
		const char *cells_name,
		int cell_count)
{
	const __be32 *list;
	int size;

	memset(it, 0, sizeof(*it));

	/*
	 * one of cell_count or cells_name must be provided to determine the
	 * argument length.
	 */
	if (cell_count < 0 && !cells_name)
		return -EINVAL;

	list = of_get_property(np, list_name, &size);
	if (!list)
		return -ENOENT;

	it->cells_name = cells_name;
	it->cell_count = cell_count;
	it->parent = np;
	it->list_end = list + size / sizeof(*list);
	it->phandle_end = list;
	it->cur = list;

	return 0;
}