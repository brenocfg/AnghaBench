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
struct TYPE_2__ {int /*<<< orphan*/  lp; } ;
struct vdc_port {TYPE_1__ vio; } ;

/* Variables and functions */
 int /*<<< orphan*/  ldc_disconnect (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldc_unbind (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vdc_free_tx_ring (struct vdc_port*) ; 
 int /*<<< orphan*/  vio_ldc_free (TYPE_1__*) ; 

__attribute__((used)) static void vdc_port_down(struct vdc_port *port)
{
	ldc_disconnect(port->vio.lp);
	ldc_unbind(port->vio.lp);
	vdc_free_tx_ring(port);
	vio_ldc_free(&port->vio);
}