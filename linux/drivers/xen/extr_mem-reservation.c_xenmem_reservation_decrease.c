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
typedef  int /*<<< orphan*/  xen_pfn_t ;
struct xen_memory_reservation {int nr_extents; int /*<<< orphan*/  extent_start; int /*<<< orphan*/  domid; int /*<<< orphan*/  extent_order; int /*<<< orphan*/  address_bits; } ;

/* Variables and functions */
 int /*<<< orphan*/  DOMID_SELF ; 
 int /*<<< orphan*/  EXTENT_ORDER ; 
 int HYPERVISOR_memory_op (int /*<<< orphan*/ ,struct xen_memory_reservation*) ; 
 int /*<<< orphan*/  XENMEM_decrease_reservation ; 
 int /*<<< orphan*/  set_xen_guest_handle (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int xenmem_reservation_decrease(int count, xen_pfn_t *frames)
{
	struct xen_memory_reservation reservation = {
		.address_bits = 0,
		.extent_order = EXTENT_ORDER,
		.domid        = DOMID_SELF
	};

	/* XENMEM_decrease_reservation requires a GFN */
	set_xen_guest_handle(reservation.extent_start, frames);
	reservation.nr_extents = count;
	return HYPERVISOR_memory_op(XENMEM_decrease_reservation, &reservation);
}