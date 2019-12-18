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
struct uart_port {int dummy; } ;
struct sci_port {int rx_trigger; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 struct uart_port* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 struct sci_port* to_sci_port (struct uart_port*) ; 

__attribute__((used)) static ssize_t rx_fifo_trigger_show(struct device *dev,
				    struct device_attribute *attr, char *buf)
{
	struct uart_port *port = dev_get_drvdata(dev);
	struct sci_port *sci = to_sci_port(port);

	return sprintf(buf, "%d\n", sci->rx_trigger);
}