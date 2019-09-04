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
struct device_node {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dlpar_detach_node (struct device_node*) ; 
 struct device_node* of_find_node_by_phandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 

__attribute__((used)) static int delete_dt_node(__be32 phandle)
{
	struct device_node *dn;

	dn = of_find_node_by_phandle(be32_to_cpu(phandle));
	if (!dn)
		return -ENOENT;

	dlpar_detach_node(dn);
	of_node_put(dn);
	return 0;
}