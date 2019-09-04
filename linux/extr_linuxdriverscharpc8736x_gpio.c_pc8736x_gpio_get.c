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
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ PORT_IN ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,unsigned int,scalar_t__,int,int) ; 
 int inb_p (scalar_t__) ; 
 scalar_t__ pc8736x_gpio_base ; 
 TYPE_1__* pdev ; 
 scalar_t__* port_offset ; 

__attribute__((used)) static int pc8736x_gpio_get(unsigned minor)
{
	int port, bit, val;

	port = minor >> 3;
	bit = minor & 7;
	val = inb_p(pc8736x_gpio_base + port_offset[port] + PORT_IN);
	val >>= bit;
	val &= 1;

	dev_dbg(&pdev->dev, "_gpio_get(%d from %x bit %d) == val %d\n",
		minor, pc8736x_gpio_base + port_offset[port] + PORT_IN, bit,
		val);

	return val;
}