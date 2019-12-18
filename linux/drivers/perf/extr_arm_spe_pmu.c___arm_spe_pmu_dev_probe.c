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
typedef  int u64 ;
struct device {int dummy; } ;
struct arm_spe_pmu {int align; int min_period; int max_record_sz; int counter_sz; int /*<<< orphan*/  features; int /*<<< orphan*/  supported_cpus; TYPE_1__* pdev; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ID_AA64DFR0_EL1 ; 
 int /*<<< orphan*/  ID_AA64DFR0_PMSVER_SHIFT ; 
 int /*<<< orphan*/  SPE_PMU_FEAT_ARCH_INST ; 
 int /*<<< orphan*/  SPE_PMU_FEAT_DEV_PROBED ; 
 int /*<<< orphan*/  SPE_PMU_FEAT_ERND ; 
 int /*<<< orphan*/  SPE_PMU_FEAT_FILT_EVT ; 
 int /*<<< orphan*/  SPE_PMU_FEAT_FILT_LAT ; 
 int /*<<< orphan*/  SPE_PMU_FEAT_FILT_TYP ; 
 int /*<<< orphan*/  SPE_PMU_FEAT_LDS ; 
 int /*<<< orphan*/  SYS_PMBIDR_EL1 ; 
 int SYS_PMBIDR_EL1_ALIGN_MASK ; 
 int SYS_PMBIDR_EL1_ALIGN_SHIFT ; 
 int /*<<< orphan*/  SYS_PMBIDR_EL1_P_SHIFT ; 
 int /*<<< orphan*/  SYS_PMSIDR_EL1 ; 
 int /*<<< orphan*/  SYS_PMSIDR_EL1_ARCHINST_SHIFT ; 
 int SYS_PMSIDR_EL1_COUNTSIZE_MASK ; 
 int SYS_PMSIDR_EL1_COUNTSIZE_SHIFT ; 
 int /*<<< orphan*/  SYS_PMSIDR_EL1_ERND_SHIFT ; 
 int /*<<< orphan*/  SYS_PMSIDR_EL1_FE_SHIFT ; 
 int /*<<< orphan*/  SYS_PMSIDR_EL1_FL_SHIFT ; 
 int /*<<< orphan*/  SYS_PMSIDR_EL1_FT_SHIFT ; 
 int SYS_PMSIDR_EL1_INTERVAL_MASK ; 
 int SYS_PMSIDR_EL1_INTERVAL_SHIFT ; 
 int /*<<< orphan*/  SYS_PMSIDR_EL1_LDS_SHIFT ; 
 int SYS_PMSIDR_EL1_MAXSIZE_MASK ; 
 int SYS_PMSIDR_EL1_MAXSIZE_SHIFT ; 
 int SZ_2K ; 
 int cpuid_feature_extract_unsigned_field (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpumask_pr_args (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*,int) ; 
 int /*<<< orphan*/  read_cpuid (int /*<<< orphan*/ ) ; 
 int read_sysreg_s (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_processor_id () ; 

__attribute__((used)) static void __arm_spe_pmu_dev_probe(void *info)
{
	int fld;
	u64 reg;
	struct arm_spe_pmu *spe_pmu = info;
	struct device *dev = &spe_pmu->pdev->dev;

	fld = cpuid_feature_extract_unsigned_field(read_cpuid(ID_AA64DFR0_EL1),
						   ID_AA64DFR0_PMSVER_SHIFT);
	if (!fld) {
		dev_err(dev,
			"unsupported ID_AA64DFR0_EL1.PMSVer [%d] on CPU %d\n",
			fld, smp_processor_id());
		return;
	}

	/* Read PMBIDR first to determine whether or not we have access */
	reg = read_sysreg_s(SYS_PMBIDR_EL1);
	if (reg & BIT(SYS_PMBIDR_EL1_P_SHIFT)) {
		dev_err(dev,
			"profiling buffer owned by higher exception level\n");
		return;
	}

	/* Minimum alignment. If it's out-of-range, then fail the probe */
	fld = reg >> SYS_PMBIDR_EL1_ALIGN_SHIFT & SYS_PMBIDR_EL1_ALIGN_MASK;
	spe_pmu->align = 1 << fld;
	if (spe_pmu->align > SZ_2K) {
		dev_err(dev, "unsupported PMBIDR.Align [%d] on CPU %d\n",
			fld, smp_processor_id());
		return;
	}

	/* It's now safe to read PMSIDR and figure out what we've got */
	reg = read_sysreg_s(SYS_PMSIDR_EL1);
	if (reg & BIT(SYS_PMSIDR_EL1_FE_SHIFT))
		spe_pmu->features |= SPE_PMU_FEAT_FILT_EVT;

	if (reg & BIT(SYS_PMSIDR_EL1_FT_SHIFT))
		spe_pmu->features |= SPE_PMU_FEAT_FILT_TYP;

	if (reg & BIT(SYS_PMSIDR_EL1_FL_SHIFT))
		spe_pmu->features |= SPE_PMU_FEAT_FILT_LAT;

	if (reg & BIT(SYS_PMSIDR_EL1_ARCHINST_SHIFT))
		spe_pmu->features |= SPE_PMU_FEAT_ARCH_INST;

	if (reg & BIT(SYS_PMSIDR_EL1_LDS_SHIFT))
		spe_pmu->features |= SPE_PMU_FEAT_LDS;

	if (reg & BIT(SYS_PMSIDR_EL1_ERND_SHIFT))
		spe_pmu->features |= SPE_PMU_FEAT_ERND;

	/* This field has a spaced out encoding, so just use a look-up */
	fld = reg >> SYS_PMSIDR_EL1_INTERVAL_SHIFT & SYS_PMSIDR_EL1_INTERVAL_MASK;
	switch (fld) {
	case 0:
		spe_pmu->min_period = 256;
		break;
	case 2:
		spe_pmu->min_period = 512;
		break;
	case 3:
		spe_pmu->min_period = 768;
		break;
	case 4:
		spe_pmu->min_period = 1024;
		break;
	case 5:
		spe_pmu->min_period = 1536;
		break;
	case 6:
		spe_pmu->min_period = 2048;
		break;
	case 7:
		spe_pmu->min_period = 3072;
		break;
	default:
		dev_warn(dev, "unknown PMSIDR_EL1.Interval [%d]; assuming 8\n",
			 fld);
		/* Fallthrough */
	case 8:
		spe_pmu->min_period = 4096;
	}

	/* Maximum record size. If it's out-of-range, then fail the probe */
	fld = reg >> SYS_PMSIDR_EL1_MAXSIZE_SHIFT & SYS_PMSIDR_EL1_MAXSIZE_MASK;
	spe_pmu->max_record_sz = 1 << fld;
	if (spe_pmu->max_record_sz > SZ_2K || spe_pmu->max_record_sz < 16) {
		dev_err(dev, "unsupported PMSIDR_EL1.MaxSize [%d] on CPU %d\n",
			fld, smp_processor_id());
		return;
	}

	fld = reg >> SYS_PMSIDR_EL1_COUNTSIZE_SHIFT & SYS_PMSIDR_EL1_COUNTSIZE_MASK;
	switch (fld) {
	default:
		dev_warn(dev, "unknown PMSIDR_EL1.CountSize [%d]; assuming 2\n",
			 fld);
		/* Fallthrough */
	case 2:
		spe_pmu->counter_sz = 12;
	}

	dev_info(dev,
		 "probed for CPUs %*pbl [max_record_sz %u, align %u, features 0x%llx]\n",
		 cpumask_pr_args(&spe_pmu->supported_cpus),
		 spe_pmu->max_record_sz, spe_pmu->align, spe_pmu->features);

	spe_pmu->features |= SPE_PMU_FEAT_DEV_PROBED;
	return;
}