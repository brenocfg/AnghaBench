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
struct pcmcia_device {int /*<<< orphan*/ * resource; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int PCMCIA_NUM_RESOURCES ; 
 int /*<<< orphan*/  sprintf (char*,char*,int /*<<< orphan*/ ) ; 
 struct pcmcia_device* to_pcmcia_dev (struct device*) ; 

__attribute__((used)) static ssize_t resources_show(struct device *dev,
			      struct device_attribute *attr, char *buf)
{
	struct pcmcia_device *p_dev = to_pcmcia_dev(dev);
	char *str = buf;
	int i;

	for (i = 0; i < PCMCIA_NUM_RESOURCES; i++)
		str += sprintf(str, "%pr\n", p_dev->resource[i]);

	return str - buf;
}