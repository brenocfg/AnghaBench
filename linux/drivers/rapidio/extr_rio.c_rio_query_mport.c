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
struct rio_mport_attr {int dummy; } ;
struct rio_mport {TYPE_1__* ops; } ;
struct TYPE_2__ {int (* query_mport ) (struct rio_mport*,struct rio_mport_attr*) ;} ;

/* Variables and functions */
 int ENODATA ; 
 int stub1 (struct rio_mport*,struct rio_mport_attr*) ; 

int rio_query_mport(struct rio_mport *port,
		    struct rio_mport_attr *mport_attr)
{
	if (!port->ops->query_mport)
		return -ENODATA;
	return port->ops->query_mport(port, mport_attr);
}