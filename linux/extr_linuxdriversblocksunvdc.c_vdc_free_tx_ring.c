#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct vio_dring_state {int entry_size; int num_entries; scalar_t__ ncookies; scalar_t__ pending; int /*<<< orphan*/ * base; int /*<<< orphan*/  cookies; } ;
struct TYPE_2__ {int /*<<< orphan*/  lp; struct vio_dring_state* drings; } ;
struct vdc_port {TYPE_1__ vio; } ;

/* Variables and functions */
 size_t VIO_DRIVER_TX_RING ; 
 int /*<<< orphan*/  ldc_free_exp_dring (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void vdc_free_tx_ring(struct vdc_port *port)
{
	struct vio_dring_state *dr = &port->vio.drings[VIO_DRIVER_TX_RING];

	if (dr->base) {
		ldc_free_exp_dring(port->vio.lp, dr->base,
				   (dr->entry_size * dr->num_entries),
				   dr->cookies, dr->ncookies);
		dr->base = NULL;
		dr->entry_size = 0;
		dr->num_entries = 0;
		dr->pending = 0;
		dr->ncookies = 0;
	}
}