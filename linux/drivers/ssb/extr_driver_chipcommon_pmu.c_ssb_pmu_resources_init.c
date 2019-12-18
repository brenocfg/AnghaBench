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
struct ssb_chipcommon {TYPE_1__* dev; } ;
struct ssb_bus {int chip_id; } ;
struct pmu_res_updown_tab_entry {int resource; int updown; } ;
struct pmu_res_depend_tab_entry {int resource; int task; int depend; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; struct ssb_bus* bus; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (void*) ; 
#define  PMU_RES_DEP_ADD 130 
#define  PMU_RES_DEP_REMOVE 129 
#define  PMU_RES_DEP_SET 128 
 int /*<<< orphan*/  SSB_CHIPCO_CHIPSTAT ; 
 int SSB_CHIPCO_CHST_4325_PMUTOP_2B ; 
 int /*<<< orphan*/  SSB_CHIPCO_PMU_MAXRES_MSK ; 
 int /*<<< orphan*/  SSB_CHIPCO_PMU_MINRES_MSK ; 
 int /*<<< orphan*/  SSB_CHIPCO_PMU_RES_DEPMSK ; 
 int /*<<< orphan*/  SSB_CHIPCO_PMU_RES_TABSEL ; 
 int /*<<< orphan*/  SSB_CHIPCO_PMU_RES_UPDNTM ; 
 int SSB_PMURES_4325_CBUCK_BURST ; 
 int SSB_PMURES_4325_CLDO_CBUCK_BURST ; 
 int SSB_PMURES_4325_LNLDO2_PU ; 
 int SSB_PMURES_4328_BB_SWITCHER_PWM ; 
 int SSB_PMURES_4328_EXT_SWITCHER_PWM ; 
 int SSB_PMURES_4328_XTAL_EN ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  chipco_mask32 (struct ssb_chipcommon*,int /*<<< orphan*/ ,int) ; 
 int chipco_read32 (struct ssb_chipcommon*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  chipco_set32 (struct ssb_chipcommon*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  chipco_write32 (struct ssb_chipcommon*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 void* pmu_res_depend_tab_4325a0 ; 
 void* pmu_res_depend_tab_4328a0 ; 
 void* pmu_res_updown_tab_4325a0 ; 
 void* pmu_res_updown_tab_4328a0 ; 

__attribute__((used)) static void ssb_pmu_resources_init(struct ssb_chipcommon *cc)
{
	struct ssb_bus *bus = cc->dev->bus;
	u32 min_msk = 0, max_msk = 0;
	unsigned int i;
	const struct pmu_res_updown_tab_entry *updown_tab = NULL;
	unsigned int updown_tab_size = 0;
	const struct pmu_res_depend_tab_entry *depend_tab = NULL;
	unsigned int depend_tab_size = 0;

	switch (bus->chip_id) {
	case 0x4312:
		 min_msk = 0xCBB;
		 break;
	case 0x4322:
	case 43222:
		/* We keep the default settings:
		 * min_msk = 0xCBB
		 * max_msk = 0x7FFFF
		 */
		break;
	case 0x4325:
		/* Power OTP down later. */
		min_msk = (1 << SSB_PMURES_4325_CBUCK_BURST) |
			  (1 << SSB_PMURES_4325_LNLDO2_PU);
		if (chipco_read32(cc, SSB_CHIPCO_CHIPSTAT) &
		    SSB_CHIPCO_CHST_4325_PMUTOP_2B)
			min_msk |= (1 << SSB_PMURES_4325_CLDO_CBUCK_BURST);
		/* The PLL may turn on, if it decides so. */
		max_msk = 0xFFFFF;
		updown_tab = pmu_res_updown_tab_4325a0;
		updown_tab_size = ARRAY_SIZE(pmu_res_updown_tab_4325a0);
		depend_tab = pmu_res_depend_tab_4325a0;
		depend_tab_size = ARRAY_SIZE(pmu_res_depend_tab_4325a0);
		break;
	case 0x4328:
		min_msk = (1 << SSB_PMURES_4328_EXT_SWITCHER_PWM) |
			  (1 << SSB_PMURES_4328_BB_SWITCHER_PWM) |
			  (1 << SSB_PMURES_4328_XTAL_EN);
		/* The PLL may turn on, if it decides so. */
		max_msk = 0xFFFFF;
		updown_tab = pmu_res_updown_tab_4328a0;
		updown_tab_size = ARRAY_SIZE(pmu_res_updown_tab_4328a0);
		depend_tab = pmu_res_depend_tab_4328a0;
		depend_tab_size = ARRAY_SIZE(pmu_res_depend_tab_4328a0);
		break;
	case 0x5354:
		/* The PLL may turn on, if it decides so. */
		max_msk = 0xFFFFF;
		break;
	default:
		dev_err(cc->dev->dev, "ERROR: PMU resource config unknown for device %04X\n",
			bus->chip_id);
	}

	if (updown_tab) {
		for (i = 0; i < updown_tab_size; i++) {
			chipco_write32(cc, SSB_CHIPCO_PMU_RES_TABSEL,
				       updown_tab[i].resource);
			chipco_write32(cc, SSB_CHIPCO_PMU_RES_UPDNTM,
				       updown_tab[i].updown);
		}
	}
	if (depend_tab) {
		for (i = 0; i < depend_tab_size; i++) {
			chipco_write32(cc, SSB_CHIPCO_PMU_RES_TABSEL,
				       depend_tab[i].resource);
			switch (depend_tab[i].task) {
			case PMU_RES_DEP_SET:
				chipco_write32(cc, SSB_CHIPCO_PMU_RES_DEPMSK,
					       depend_tab[i].depend);
				break;
			case PMU_RES_DEP_ADD:
				chipco_set32(cc, SSB_CHIPCO_PMU_RES_DEPMSK,
					     depend_tab[i].depend);
				break;
			case PMU_RES_DEP_REMOVE:
				chipco_mask32(cc, SSB_CHIPCO_PMU_RES_DEPMSK,
					      ~(depend_tab[i].depend));
				break;
			default:
				WARN_ON(1);
			}
		}
	}

	/* Set the resource masks. */
	if (min_msk)
		chipco_write32(cc, SSB_CHIPCO_PMU_MINRES_MSK, min_msk);
	if (max_msk)
		chipco_write32(cc, SSB_CHIPCO_PMU_MAXRES_MSK, max_msk);
}