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
struct drm_dp_mst_topology_mgr {int dummy; } ;
struct TYPE_2__ {scalar_t__ num_slots; } ;
struct drm_dp_mst_port {TYPE_1__ vcpi; } ;

/* Variables and functions */

void drm_dp_mst_reset_vcpi_slots(struct drm_dp_mst_topology_mgr *mgr, struct drm_dp_mst_port *port)
{
	/*
	 * A port with VCPI will remain allocated until its VCPI is
	 * released, no verified ref needed
	 */

	port->vcpi.num_slots = 0;
}