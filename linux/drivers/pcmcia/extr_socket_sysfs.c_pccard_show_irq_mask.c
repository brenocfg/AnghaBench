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
struct pcmcia_socket {int irq_mask; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 struct pcmcia_socket* to_socket (struct device*) ; 

__attribute__((used)) static ssize_t pccard_show_irq_mask(struct device *dev,
				    struct device_attribute *attr,
				    char *buf)
{
	struct pcmcia_socket *s = to_socket(dev);
	return sprintf(buf, "0x%04x\n", s->irq_mask);
}