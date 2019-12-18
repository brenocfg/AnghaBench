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
typedef  scalar_t__ u32 ;
typedef  size_t u16 ;
struct spmi_pmic_arb {size_t last_apid; scalar_t__ core_size; scalar_t__ cnfg; scalar_t__ core; size_t* ppid_to_apid; TYPE_1__* ver_ops; struct apid_data* apid_data; } ;
struct apid_data {size_t ppid; int /*<<< orphan*/  irq_ee; int /*<<< orphan*/  write_ee; } ;
struct TYPE_2__ {scalar_t__ (* apid_map_offset ) (size_t) ;} ;

/* Variables and functions */
 size_t PMIC_ARB_APID_VALID ; 
 scalar_t__ PMIC_ARB_PPID_MASK ; 
 int /*<<< orphan*/  SPMI_OWNERSHIP_PERIPH2OWNER (scalar_t__) ; 
 scalar_t__ SPMI_OWNERSHIP_TABLE_REG (size_t) ; 
 scalar_t__ readl_relaxed (scalar_t__) ; 
 scalar_t__ stub1 (size_t) ; 

__attribute__((used)) static u16 pmic_arb_find_apid(struct spmi_pmic_arb *pmic_arb, u16 ppid)
{
	struct apid_data *apidd = &pmic_arb->apid_data[pmic_arb->last_apid];
	u32 regval, offset;
	u16 id, apid;

	for (apid = pmic_arb->last_apid; ; apid++, apidd++) {
		offset = pmic_arb->ver_ops->apid_map_offset(apid);
		if (offset >= pmic_arb->core_size)
			break;

		regval = readl_relaxed(pmic_arb->cnfg +
				      SPMI_OWNERSHIP_TABLE_REG(apid));
		apidd->irq_ee = SPMI_OWNERSHIP_PERIPH2OWNER(regval);
		apidd->write_ee = apidd->irq_ee;

		regval = readl_relaxed(pmic_arb->core + offset);
		if (!regval)
			continue;

		id = (regval >> 8) & PMIC_ARB_PPID_MASK;
		pmic_arb->ppid_to_apid[id] = apid | PMIC_ARB_APID_VALID;
		apidd->ppid = id;
		if (id == ppid) {
			apid |= PMIC_ARB_APID_VALID;
			break;
		}
	}
	pmic_arb->last_apid = apid & ~PMIC_ARB_APID_VALID;

	return apid;
}