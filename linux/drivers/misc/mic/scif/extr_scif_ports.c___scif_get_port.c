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
struct scif_port {int /*<<< orphan*/  ref_cnt; } ;
struct TYPE_2__ {int /*<<< orphan*/  port_lock; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int idr_alloc (int /*<<< orphan*/ *,struct scif_port*,int,int,int /*<<< orphan*/ ) ; 
 struct scif_port* kzalloc (int,int /*<<< orphan*/ ) ; 
 TYPE_1__ scif_info ; 
 int /*<<< orphan*/  scif_ports ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int __scif_get_port(int start, int end)
{
	int id;
	struct scif_port *port = kzalloc(sizeof(*port), GFP_ATOMIC);

	if (!port)
		return -ENOMEM;
	spin_lock(&scif_info.port_lock);
	id = idr_alloc(&scif_ports, port, start, end, GFP_ATOMIC);
	if (id >= 0)
		port->ref_cnt++;
	spin_unlock(&scif_info.port_lock);
	return id;
}