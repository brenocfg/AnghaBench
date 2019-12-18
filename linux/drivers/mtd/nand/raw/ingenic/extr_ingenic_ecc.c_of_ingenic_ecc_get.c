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
struct ingenic_ecc {int dummy; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 struct ingenic_ecc* ingenic_ecc_get (struct device_node*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 struct device_node* of_parse_phandle (struct device_node*,char*,int /*<<< orphan*/ ) ; 

struct ingenic_ecc *of_ingenic_ecc_get(struct device_node *of_node)
{
	struct ingenic_ecc *ecc = NULL;
	struct device_node *np;

	np = of_parse_phandle(of_node, "ecc-engine", 0);

	/*
	 * If the ecc-engine property is not found, check for the deprecated
	 * ingenic,bch-controller property
	 */
	if (!np)
		np = of_parse_phandle(of_node, "ingenic,bch-controller", 0);

	if (np) {
		ecc = ingenic_ecc_get(np);
		of_node_put(np);
	}
	return ecc;
}