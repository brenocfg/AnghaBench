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

/* Variables and functions */
 struct device_node* of_find_compatible_node (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 struct device_node* of_find_node_by_type (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static struct device_node *qe_get_device_node(void)
{
	struct device_node *qe;

	/*
	 * Newer device trees have an "fsl,qe" compatible property for the QE
	 * node, but we still need to support older device trees.
	 */
	qe = of_find_compatible_node(NULL, NULL, "fsl,qe");
	if (qe)
		return qe;
	return of_find_node_by_type(NULL, "qe");
}