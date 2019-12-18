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
struct tty_port {int dummy; } ;
struct serial_struct {unsigned long port; scalar_t__ port_high; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int HIGH_BITS_OFFSET ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 struct tty_port* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,unsigned long) ; 
 int /*<<< orphan*/  uart_get_info (struct tty_port*,struct serial_struct*) ; 

__attribute__((used)) static ssize_t uart_get_attr_port(struct device *dev,
	struct device_attribute *attr, char *buf)
{
	struct serial_struct tmp;
	struct tty_port *port = dev_get_drvdata(dev);
	unsigned long ioaddr;

	uart_get_info(port, &tmp);
	ioaddr = tmp.port;
	if (HIGH_BITS_OFFSET)
		ioaddr |= (unsigned long)tmp.port_high << HIGH_BITS_OFFSET;
	return snprintf(buf, PAGE_SIZE, "0x%lX\n", ioaddr);
}