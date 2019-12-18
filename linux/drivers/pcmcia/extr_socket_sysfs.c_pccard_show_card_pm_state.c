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
struct pcmcia_socket {int state; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int SOCKET_SUSPEND ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 
 struct pcmcia_socket* to_socket (struct device*) ; 

__attribute__((used)) static ssize_t pccard_show_card_pm_state(struct device *dev,
					 struct device_attribute *attr,
					 char *buf)
{
	struct pcmcia_socket *s = to_socket(dev);
	return sprintf(buf, "%s\n", s->state & SOCKET_SUSPEND ? "off" : "on");
}