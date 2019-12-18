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
struct uio_port {size_t porttype; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 size_t UIO_PORT_OTHER ; 
 int /*<<< orphan*/  sprintf (char*,char*,char const*) ; 

__attribute__((used)) static ssize_t portio_porttype_show(struct uio_port *port, char *buf)
{
	const char *porttypes[] = {"none", "x86", "gpio", "other"};

	if ((port->porttype < 0) || (port->porttype > UIO_PORT_OTHER))
		return -EINVAL;

	return sprintf(buf, "port_%s\n", porttypes[port->porttype]);
}