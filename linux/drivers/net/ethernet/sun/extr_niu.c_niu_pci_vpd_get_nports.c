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
struct TYPE_2__ {int /*<<< orphan*/  model; } ;
struct niu {TYPE_1__ vpd; } ;

/* Variables and functions */
 int /*<<< orphan*/  NIU_2XGF_LP_MDL_STR ; 
 int /*<<< orphan*/  NIU_2XGF_MRVL_MDL_STR ; 
 int /*<<< orphan*/  NIU_2XGF_PEM_MDL_STR ; 
 int /*<<< orphan*/  NIU_ALONSO_MDL_STR ; 
 int /*<<< orphan*/  NIU_FOXXY_MDL_STR ; 
 int /*<<< orphan*/  NIU_KIMI_MDL_STR ; 
 int /*<<< orphan*/  NIU_MARAMBA_MDL_STR ; 
 int /*<<< orphan*/  NIU_QGC_LP_MDL_STR ; 
 int /*<<< orphan*/  NIU_QGC_PEM_MDL_STR ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int niu_pci_vpd_get_nports(struct niu *np)
{
	int ports = 0;

	if ((!strcmp(np->vpd.model, NIU_QGC_LP_MDL_STR)) ||
	    (!strcmp(np->vpd.model, NIU_QGC_PEM_MDL_STR)) ||
	    (!strcmp(np->vpd.model, NIU_MARAMBA_MDL_STR)) ||
	    (!strcmp(np->vpd.model, NIU_KIMI_MDL_STR)) ||
	    (!strcmp(np->vpd.model, NIU_ALONSO_MDL_STR))) {
		ports = 4;
	} else if ((!strcmp(np->vpd.model, NIU_2XGF_LP_MDL_STR)) ||
		   (!strcmp(np->vpd.model, NIU_2XGF_PEM_MDL_STR)) ||
		   (!strcmp(np->vpd.model, NIU_FOXXY_MDL_STR)) ||
		   (!strcmp(np->vpd.model, NIU_2XGF_MRVL_MDL_STR))) {
		ports = 2;
	}

	return ports;
}