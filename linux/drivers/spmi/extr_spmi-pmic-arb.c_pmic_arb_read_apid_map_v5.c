#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
typedef  size_t u16 ;
struct spmi_pmic_arb {scalar_t__ core_size; scalar_t__ core; scalar_t__ cnfg; size_t* ppid_to_apid; scalar_t__ ee; size_t last_apid; TYPE_2__* spmic; struct apid_data* apid_data; TYPE_1__* ver_ops; } ;
struct apid_data {scalar_t__ write_ee; scalar_t__ irq_ee; size_t ppid; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {scalar_t__ (* apid_map_offset ) (size_t) ;} ;

/* Variables and functions */
 scalar_t__ INVALID_EE ; 
 size_t PMIC_ARB_APID_VALID ; 
 int PMIC_ARB_CHAN_IS_IRQ_OWNER (scalar_t__) ; 
 size_t PMIC_ARB_MAX_PPID ; 
 scalar_t__ PMIC_ARB_PPID_MASK ; 
 scalar_t__ SPMI_OWNERSHIP_PERIPH2OWNER (scalar_t__) ; 
 scalar_t__ SPMI_OWNERSHIP_TABLE_REG (size_t) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,...) ; 
 scalar_t__ readl_relaxed (scalar_t__) ; 
 scalar_t__ stub1 (size_t) ; 

__attribute__((used)) static int pmic_arb_read_apid_map_v5(struct spmi_pmic_arb *pmic_arb)
{
	struct apid_data *apidd = pmic_arb->apid_data;
	struct apid_data *prev_apidd;
	u16 i, apid, ppid;
	bool valid, is_irq_ee;
	u32 regval, offset;

	/*
	 * In order to allow multiple EEs to write to a single PPID in arbiter
	 * version 5, there is more than one APID mapped to each PPID.
	 * The owner field for each of these mappings specifies the EE which is
	 * allowed to write to the APID.  The owner of the last (highest) APID
	 * for a given PPID will receive interrupts from the PPID.
	 */
	for (i = 0; ; i++, apidd++) {
		offset = pmic_arb->ver_ops->apid_map_offset(i);
		if (offset >= pmic_arb->core_size)
			break;

		regval = readl_relaxed(pmic_arb->core + offset);
		if (!regval)
			continue;
		ppid = (regval >> 8) & PMIC_ARB_PPID_MASK;
		is_irq_ee = PMIC_ARB_CHAN_IS_IRQ_OWNER(regval);

		regval = readl_relaxed(pmic_arb->cnfg +
				      SPMI_OWNERSHIP_TABLE_REG(i));
		apidd->write_ee = SPMI_OWNERSHIP_PERIPH2OWNER(regval);

		apidd->irq_ee = is_irq_ee ? apidd->write_ee : INVALID_EE;

		valid = pmic_arb->ppid_to_apid[ppid] & PMIC_ARB_APID_VALID;
		apid = pmic_arb->ppid_to_apid[ppid] & ~PMIC_ARB_APID_VALID;
		prev_apidd = &pmic_arb->apid_data[apid];

		if (valid && is_irq_ee &&
				prev_apidd->write_ee == pmic_arb->ee) {
			/*
			 * Duplicate PPID mapping after the one for this EE;
			 * override the irq owner
			 */
			prev_apidd->irq_ee = apidd->irq_ee;
		} else if (!valid || is_irq_ee) {
			/* First PPID mapping or duplicate for another EE */
			pmic_arb->ppid_to_apid[ppid] = i | PMIC_ARB_APID_VALID;
		}

		apidd->ppid = ppid;
		pmic_arb->last_apid = i;
	}

	/* Dump the mapping table for debug purposes. */
	dev_dbg(&pmic_arb->spmic->dev, "PPID APID Write-EE IRQ-EE\n");
	for (ppid = 0; ppid < PMIC_ARB_MAX_PPID; ppid++) {
		apid = pmic_arb->ppid_to_apid[ppid];
		if (apid & PMIC_ARB_APID_VALID) {
			apid &= ~PMIC_ARB_APID_VALID;
			apidd = &pmic_arb->apid_data[apid];
			dev_dbg(&pmic_arb->spmic->dev, "%#03X %3u %2u %2u\n",
			      ppid, apid, apidd->write_ee, apidd->irq_ee);
		}
	}

	return 0;
}