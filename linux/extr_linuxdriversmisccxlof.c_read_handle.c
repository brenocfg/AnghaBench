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
typedef  scalar_t__ u64 ;
struct device_node {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/ * of_get_address (struct device_node*,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_n_addr_cells (struct device_node*) ; 
 scalar_t__ of_read_number (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int read_handle(struct device_node *np, u64 *handle)
{
	const __be32 *prop;
	u64 size;

	/* Get address and size of the node */
	prop = of_get_address(np, 0, &size, NULL);
	if (size)
		return -EINVAL;

	/* Helper to read a big number; size is in cells (not bytes) */
	*handle = of_read_number(prop, of_n_addr_cells(np));
	return 0;
}