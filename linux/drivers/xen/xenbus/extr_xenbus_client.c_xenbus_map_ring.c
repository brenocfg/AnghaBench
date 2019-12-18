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
struct xenbus_device {int dummy; } ;
typedef  unsigned long phys_addr_t ;
typedef  int /*<<< orphan*/  grant_ref_t ;
typedef  int /*<<< orphan*/  grant_handle_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  GNTMAP_host_map ; 
 int XENBUS_MAX_RING_GRANTS ; 
 int __xenbus_map_ring (struct xenbus_device*,int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ *,unsigned long*,int /*<<< orphan*/ ,int*) ; 

int xenbus_map_ring(struct xenbus_device *dev, grant_ref_t *gnt_refs,
		    unsigned int nr_grefs, grant_handle_t *handles,
		    unsigned long *vaddrs, bool *leaked)
{
	phys_addr_t phys_addrs[XENBUS_MAX_RING_GRANTS];
	int i;

	if (nr_grefs > XENBUS_MAX_RING_GRANTS)
		return -EINVAL;

	for (i = 0; i < nr_grefs; i++)
		phys_addrs[i] = (unsigned long)vaddrs[i];

	return __xenbus_map_ring(dev, gnt_refs, nr_grefs, handles,
				 phys_addrs, GNTMAP_host_map, leaked);
}