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
struct mtk_ecc {int dummy; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 struct mtk_ecc* mtk_ecc_get (struct device_node*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 struct device_node* of_parse_phandle (struct device_node*,char*,int /*<<< orphan*/ ) ; 

struct mtk_ecc *of_mtk_ecc_get(struct device_node *of_node)
{
	struct mtk_ecc *ecc = NULL;
	struct device_node *np;

	np = of_parse_phandle(of_node, "ecc-engine", 0);
	if (np) {
		ecc = mtk_ecc_get(np);
		of_node_put(np);
	}

	return ecc;
}