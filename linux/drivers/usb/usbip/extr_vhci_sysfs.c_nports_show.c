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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int VHCI_PORTS ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 int vhci_num_controllers ; 

__attribute__((used)) static ssize_t nports_show(struct device *dev, struct device_attribute *attr,
			   char *out)
{
	char *s = out;

	/*
	 * Half the ports are for SPEED_HIGH and half for SPEED_SUPER,
	 * thus the * 2.
	 */
	out += sprintf(out, "%d\n", VHCI_PORTS * vhci_num_controllers);
	return out - s;
}