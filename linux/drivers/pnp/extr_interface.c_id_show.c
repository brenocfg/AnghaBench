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
struct pnp_id {char* id; struct pnp_id* next; } ;
struct pnp_dev {struct pnp_id* id; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 
 struct pnp_dev* to_pnp_dev (struct device*) ; 

__attribute__((used)) static ssize_t id_show(struct device *dmdev, struct device_attribute *attr,
		       char *buf)
{
	char *str = buf;
	struct pnp_dev *dev = to_pnp_dev(dmdev);
	struct pnp_id *pos = dev->id;

	while (pos) {
		str += sprintf(str, "%s\n", pos->id);
		pos = pos->next;
	}
	return (str - buf);
}