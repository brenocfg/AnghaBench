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
struct uart_port {scalar_t__ type; int /*<<< orphan*/  dev; } ;
struct sccnxp_port {TYPE_1__* chip; } ;
struct TYPE_2__ {char const* name; } ;

/* Variables and functions */
 scalar_t__ PORT_SC26XX ; 
 struct sccnxp_port* dev_get_drvdata (int /*<<< orphan*/ ) ; 

__attribute__((used)) static const char *sccnxp_type(struct uart_port *port)
{
	struct sccnxp_port *s = dev_get_drvdata(port->dev);

	return (port->type == PORT_SC26XX) ? s->chip->name : NULL;
}