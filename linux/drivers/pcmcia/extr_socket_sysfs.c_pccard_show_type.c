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
 int /*<<< orphan*/  ENODEV ; 
 int SOCKET_CARDBUS ; 
 int SOCKET_PRESENT ; 
 int /*<<< orphan*/  sprintf (char*,char*) ; 
 struct pcmcia_socket* to_socket (struct device*) ; 

__attribute__((used)) static ssize_t pccard_show_type(struct device *dev, struct device_attribute *attr,
				char *buf)
{
	struct pcmcia_socket *s = to_socket(dev);

	if (!(s->state & SOCKET_PRESENT))
		return -ENODEV;
	if (s->state & SOCKET_CARDBUS)
		return sprintf(buf, "32-bit\n");
	return sprintf(buf, "16-bit\n");
}