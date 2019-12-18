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
typedef  int u8 ;
struct uart_port {int regshift; scalar_t__ membase; int /*<<< orphan*/  dev; } ;
struct sccnxp_port {TYPE_1__* chip; } ;
struct TYPE_2__ {int /*<<< orphan*/  trwd; } ;

/* Variables and functions */
 struct sccnxp_port* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ndelay (int /*<<< orphan*/ ) ; 
 int readb (scalar_t__) ; 

__attribute__((used)) static u8 sccnxp_read(struct uart_port *port, u8 reg)
{
	struct sccnxp_port *s = dev_get_drvdata(port->dev);
	u8 ret;

	ret = readb(port->membase + (reg << port->regshift));

	ndelay(s->chip->trwd);

	return ret;
}