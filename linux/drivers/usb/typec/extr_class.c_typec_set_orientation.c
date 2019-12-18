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
struct typec_port {int orientation; TYPE_1__* sw; } ;
typedef  enum typec_orientation { ____Placeholder_typec_orientation } typec_orientation ;
struct TYPE_2__ {int (* set ) (TYPE_1__*,int) ;} ;

/* Variables and functions */
 int stub1 (TYPE_1__*,int) ; 

int typec_set_orientation(struct typec_port *port,
			  enum typec_orientation orientation)
{
	int ret;

	if (port->sw) {
		ret = port->sw->set(port->sw, orientation);
		if (ret)
			return ret;
	}

	port->orientation = orientation;

	return 0;
}