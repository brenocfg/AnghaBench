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
struct unmap_ring_vfree_hvm {unsigned long* addrs; size_t idx; } ;

/* Variables and functions */
 scalar_t__ gfn_to_virt (unsigned long) ; 

__attribute__((used)) static void xenbus_unmap_ring_setup_grant_hvm(unsigned long gfn,
					      unsigned int goffset,
					      unsigned int len,
					      void *data)
{
	struct unmap_ring_vfree_hvm *info = data;

	info->addrs[info->idx] = (unsigned long)gfn_to_virt(gfn);

	info->idx++;
}