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
struct pcmcia_socket {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t EINVAL ; 
 int /*<<< orphan*/  PCMCIA_UEVENT_INSERT ; 
 int /*<<< orphan*/  pcmcia_parse_uevents (struct pcmcia_socket*,int /*<<< orphan*/ ) ; 
 struct pcmcia_socket* to_socket (struct device*) ; 

__attribute__((used)) static ssize_t pccard_store_insert(struct device *dev, struct device_attribute *attr,
				   const char *buf, size_t count)
{
	struct pcmcia_socket *s = to_socket(dev);

	if (!count)
		return -EINVAL;

	pcmcia_parse_uevents(s, PCMCIA_UEVENT_INSERT);

	return count;
}