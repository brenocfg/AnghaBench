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
typedef  int /*<<< orphan*/  u16 ;
struct scif_port {int /*<<< orphan*/  ref_cnt; } ;
struct TYPE_2__ {int /*<<< orphan*/  port_lock; } ;

/* Variables and functions */
 struct scif_port* idr_find (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__ scif_info ; 
 int /*<<< orphan*/  scif_ports ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void scif_get_port(u16 id)
{
	struct scif_port *port;

	if (!id)
		return;
	spin_lock(&scif_info.port_lock);
	port = idr_find(&scif_ports, id);
	if (port)
		port->ref_cnt++;
	spin_unlock(&scif_info.port_lock);
}