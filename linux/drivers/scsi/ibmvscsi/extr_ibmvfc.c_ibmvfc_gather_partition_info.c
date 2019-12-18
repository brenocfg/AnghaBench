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
struct ibmvfc_host {unsigned int partition_number; int /*<<< orphan*/  partition_name; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 struct device_node* of_find_node_by_path (char*) ; 
 void* of_get_property (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,char const*,int) ; 

__attribute__((used)) static void ibmvfc_gather_partition_info(struct ibmvfc_host *vhost)
{
	struct device_node *rootdn;
	const char *name;
	const unsigned int *num;

	rootdn = of_find_node_by_path("/");
	if (!rootdn)
		return;

	name = of_get_property(rootdn, "ibm,partition-name", NULL);
	if (name)
		strncpy(vhost->partition_name, name, sizeof(vhost->partition_name));
	num = of_get_property(rootdn, "ibm,partition-no", NULL);
	if (num)
		vhost->partition_number = *num;
	of_node_put(rootdn);
}