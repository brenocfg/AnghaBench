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
typedef  scalar_t__ uint32_t ;
struct device_node {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  dev_warn (struct device*,char*,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/ * of_get_property (struct device_node*,char*,unsigned int*) ; 
 unsigned int of_n_addr_cells (struct device_node*) ; 
 unsigned int of_n_size_cells (struct device_node*) ; 
 int /*<<< orphan*/  of_node_full_name (struct device_node*) ; 
 scalar_t__ of_read_number (int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static bool fsi_device_node_matches(struct device *dev, struct device_node *np,
		uint32_t addr, uint32_t size)
{
	unsigned int len, na, ns;
	const __be32 *prop;
	uint32_t psize;

	na = of_n_addr_cells(np);
	ns = of_n_size_cells(np);

	if (na != 1 || ns != 1)
		return false;

	prop = of_get_property(np, "reg", &len);
	if (!prop || len != 8)
		return false;

	if (of_read_number(prop, 1) != addr)
		return false;

	psize = of_read_number(prop + 1, 1);
	if (psize != size) {
		dev_warn(dev,
			"node %s matches probed address, but not size (got 0x%x, expected 0x%x)",
			of_node_full_name(np), psize, size);
	}

	return true;
}