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
struct gameport {char* name; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 
 struct gameport* to_gameport_port (struct device*) ; 

__attribute__((used)) static ssize_t gameport_description_show(struct device *dev, struct device_attribute *attr, char *buf)
{
	struct gameport *gameport = to_gameport_port(dev);

	return sprintf(buf, "%s\n", gameport->name);
}