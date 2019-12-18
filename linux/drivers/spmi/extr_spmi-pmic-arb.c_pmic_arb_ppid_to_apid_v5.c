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
typedef  size_t u16 ;
struct spmi_pmic_arb {int* ppid_to_apid; } ;

/* Variables and functions */
 int ENODEV ; 
 int PMIC_ARB_APID_VALID ; 

__attribute__((used)) static int pmic_arb_ppid_to_apid_v5(struct spmi_pmic_arb *pmic_arb, u16 ppid)
{
	if (!(pmic_arb->ppid_to_apid[ppid] & PMIC_ARB_APID_VALID))
		return -ENODEV;

	return pmic_arb->ppid_to_apid[ppid] & ~PMIC_ARB_APID_VALID;
}