#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  name; } ;
struct device_attribute {TYPE_1__ attr; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  sprintf (char*,char*) ; 
 int status_name_to_id (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  status_show_not_ready (int,char*) ; 
 int /*<<< orphan*/  status_show_vhci (int,char*) ; 

__attribute__((used)) static ssize_t status_show(struct device *dev,
			   struct device_attribute *attr, char *out)
{
	char *s = out;
	int pdev_nr;

	out += sprintf(out,
		       "hub port sta spd dev      sockfd local_busid\n");

	pdev_nr = status_name_to_id(attr->attr.name);
	if (pdev_nr < 0)
		out += status_show_not_ready(pdev_nr, out);
	else
		out += status_show_vhci(pdev_nr, out);

	return out - s;
}