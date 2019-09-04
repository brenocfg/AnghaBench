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
struct property {int dummy; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 struct property* new_property (char*,int,unsigned char*,int /*<<< orphan*/ *) ; 
 int of_update_property (struct device_node*,struct property*) ; 
 char* parse_next_property (char*,char*,char**,int*,unsigned char**) ; 
 char* parse_node (char*,size_t,struct device_node**) ; 
 int /*<<< orphan*/  slb_set_size (int) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int /*<<< orphan*/  strlen (char*) ; 

__attribute__((used)) static int do_update_property(char *buf, size_t bufsize)
{
	struct device_node *np;
	unsigned char *value;
	char *name, *end, *next_prop;
	int length;
	struct property *newprop;
	buf = parse_node(buf, bufsize, &np);
	end = buf + bufsize;

	if (!np)
		return -ENODEV;

	next_prop = parse_next_property(buf, end, &name, &length, &value);
	if (!next_prop)
		return -EINVAL;

	if (!strlen(name))
		return -ENODEV;

	newprop = new_property(name, length, value, NULL);
	if (!newprop)
		return -ENOMEM;

	if (!strcmp(name, "slb-size") || !strcmp(name, "ibm,slb-size"))
		slb_set_size(*(int *)value);

	return of_update_property(np, newprop);
}