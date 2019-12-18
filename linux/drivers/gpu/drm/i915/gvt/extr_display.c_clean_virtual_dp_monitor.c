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
struct intel_vgpu_port {int /*<<< orphan*/ * dpcd; int /*<<< orphan*/ * edid; } ;
struct intel_vgpu {int dummy; } ;

/* Variables and functions */
 struct intel_vgpu_port* intel_vgpu_port (struct intel_vgpu*,int) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void clean_virtual_dp_monitor(struct intel_vgpu *vgpu, int port_num)
{
	struct intel_vgpu_port *port = intel_vgpu_port(vgpu, port_num);

	kfree(port->edid);
	port->edid = NULL;

	kfree(port->dpcd);
	port->dpcd = NULL;
}