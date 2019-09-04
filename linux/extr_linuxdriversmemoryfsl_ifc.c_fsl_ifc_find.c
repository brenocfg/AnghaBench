#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
typedef  int /*<<< orphan*/  phys_addr_t ;
struct TYPE_6__ {int banks; TYPE_2__* gregs; } ;
struct TYPE_5__ {TYPE_1__* cspr_cs; } ;
struct TYPE_4__ {int /*<<< orphan*/  cspr; } ;

/* Variables and functions */
 int CSPR_BA ; 
 int CSPR_V ; 
 int ENODEV ; 
 int ENOENT ; 
 int convert_ifc_address (int /*<<< orphan*/ ) ; 
 TYPE_3__* fsl_ifc_ctrl_dev ; 
 int ifc_in32 (int /*<<< orphan*/ *) ; 

int fsl_ifc_find(phys_addr_t addr_base)
{
	int i = 0;

	if (!fsl_ifc_ctrl_dev || !fsl_ifc_ctrl_dev->gregs)
		return -ENODEV;

	for (i = 0; i < fsl_ifc_ctrl_dev->banks; i++) {
		u32 cspr = ifc_in32(&fsl_ifc_ctrl_dev->gregs->cspr_cs[i].cspr);
		if (cspr & CSPR_V && (cspr & CSPR_BA) ==
				convert_ifc_address(addr_base))
			return i;
	}

	return -ENOENT;
}