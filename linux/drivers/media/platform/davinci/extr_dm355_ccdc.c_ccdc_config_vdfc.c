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
typedef  int u32 ;
struct TYPE_2__ {int vdfcsl; int vdfcuda; int vdflsft; } ;
struct ccdc_vertical_dft {int gen_dft_en; int table_size; int saturation_ctl; TYPE_1__ dft_corr_ctl; int /*<<< orphan*/  ver_dft_en; } ;

/* Variables and functions */
 int CCDC_DFCCTL_GDFCEN_MASK ; 
 int CCDC_DFCCTL_VDFCEN_MASK ; 
 int CCDC_DFCCTL_VDFCEN_SHIFT ; 
 int CCDC_DFCCTL_VDFCSL_MASK ; 
 int CCDC_DFCCTL_VDFCSL_SHIFT ; 
 int CCDC_DFCCTL_VDFCUDA_MASK ; 
 int CCDC_DFCCTL_VDFCUDA_SHIFT ; 
 int CCDC_DFCCTL_VDFC_DISABLE ; 
 int CCDC_DFCCTL_VDFLSFT_MASK ; 
 int CCDC_DFCCTL_VDFLSFT_SHIFT ; 
 int CCDC_DFCMEMCTL_DFCMARST_MASK ; 
 int CCDC_DFCMEMCTL_DFCMARST_SHIFT ; 
 int CCDC_DFCMEMCTL_INC_ADDR ; 
 int CCDC_DFT_TABLE_SIZE ; 
 int CCDC_VDC_DFCVSAT_MASK ; 
 int /*<<< orphan*/  DFCCTL ; 
 int /*<<< orphan*/  DFCMEMCTL ; 
 int /*<<< orphan*/  DFCVSAT ; 
 int EFAULT ; 
 int EINVAL ; 
 scalar_t__ ccdc_write_dfc_entry (int,struct ccdc_vertical_dft*) ; 
 int regr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regw (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ccdc_config_vdfc(struct ccdc_vertical_dft *dfc)
{
	u32 val;
	int i;

	/* Configure General Defect Correction. The table used is from IPIPE */
	val = dfc->gen_dft_en & CCDC_DFCCTL_GDFCEN_MASK;

	/* Configure Vertical Defect Correction if needed */
	if (!dfc->ver_dft_en) {
		/* Enable only General Defect Correction */
		regw(val, DFCCTL);
		return 0;
	}

	if (dfc->table_size > CCDC_DFT_TABLE_SIZE)
		return -EINVAL;

	val |= CCDC_DFCCTL_VDFC_DISABLE;
	val |= (dfc->dft_corr_ctl.vdfcsl & CCDC_DFCCTL_VDFCSL_MASK) <<
		CCDC_DFCCTL_VDFCSL_SHIFT;
	val |= (dfc->dft_corr_ctl.vdfcuda & CCDC_DFCCTL_VDFCUDA_MASK) <<
		CCDC_DFCCTL_VDFCUDA_SHIFT;
	val |= (dfc->dft_corr_ctl.vdflsft & CCDC_DFCCTL_VDFLSFT_MASK) <<
		CCDC_DFCCTL_VDFLSFT_SHIFT;
	regw(val , DFCCTL);

	/* clear address ptr to offset 0 */
	val = CCDC_DFCMEMCTL_DFCMARST_MASK << CCDC_DFCMEMCTL_DFCMARST_SHIFT;

	/* write defect table entries */
	for (i = 0; i < dfc->table_size; i++) {
		/* increment address for non zero index */
		if (i != 0)
			val = CCDC_DFCMEMCTL_INC_ADDR;
		regw(val, DFCMEMCTL);
		if (ccdc_write_dfc_entry(i, dfc) < 0)
			return -EFAULT;
	}

	/* update saturation level and enable dfc */
	regw(dfc->saturation_ctl & CCDC_VDC_DFCVSAT_MASK, DFCVSAT);
	val = regr(DFCCTL) | (CCDC_DFCCTL_VDFCEN_MASK <<
			CCDC_DFCCTL_VDFCEN_SHIFT);
	regw(val, DFCCTL);
	return 0;
}