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
typedef  int u64 ;
typedef  int u32 ;
struct mca_config {int banks; scalar_t__ bootlog; scalar_t__ monarch_timeout; int panic_timeout; } ;
struct cpuinfo_x86 {scalar_t__ x86_vendor; int x86; int x86_model; } ;
struct TYPE_4__ {scalar_t__ init; scalar_t__ ctl; } ;
struct TYPE_3__ {int overflow_recov; } ;

/* Variables and functions */
 int ARRAY_SIZE (int*) ; 
 int BIT (int) ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  MSR_K7_HWCR ; 
 scalar_t__ USEC_PER_SEC ; 
 scalar_t__ X86_VENDOR_AMD ; 
 scalar_t__ X86_VENDOR_INTEL ; 
 scalar_t__ X86_VENDOR_UNKNOWN ; 
 int /*<<< orphan*/  clear_bit (int,unsigned long*) ; 
 struct mca_config mca_cfg ; 
 TYPE_2__* mce_banks ; 
 TYPE_1__ mce_flags ; 
 int /*<<< orphan*/  msr_clear_bit (int,int) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 int /*<<< orphan*/  quirk_no_way_out ; 
 int /*<<< orphan*/  quirk_sandybridge_ifu ; 
 int /*<<< orphan*/  rdmsrl (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wrmsrl (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int __mcheck_cpu_apply_quirks(struct cpuinfo_x86 *c)
{
	struct mca_config *cfg = &mca_cfg;

	if (c->x86_vendor == X86_VENDOR_UNKNOWN) {
		pr_info("unknown CPU type - not enabling MCE support\n");
		return -EOPNOTSUPP;
	}

	/* This should be disabled by the BIOS, but isn't always */
	if (c->x86_vendor == X86_VENDOR_AMD) {
		if (c->x86 == 15 && cfg->banks > 4) {
			/*
			 * disable GART TBL walk error reporting, which
			 * trips off incorrectly with the IOMMU & 3ware
			 * & Cerberus:
			 */
			clear_bit(10, (unsigned long *)&mce_banks[4].ctl);
		}
		if (c->x86 < 0x11 && cfg->bootlog < 0) {
			/*
			 * Lots of broken BIOS around that don't clear them
			 * by default and leave crap in there. Don't log:
			 */
			cfg->bootlog = 0;
		}
		/*
		 * Various K7s with broken bank 0 around. Always disable
		 * by default.
		 */
		if (c->x86 == 6 && cfg->banks > 0)
			mce_banks[0].ctl = 0;

		/*
		 * overflow_recov is supported for F15h Models 00h-0fh
		 * even though we don't have a CPUID bit for it.
		 */
		if (c->x86 == 0x15 && c->x86_model <= 0xf)
			mce_flags.overflow_recov = 1;

		/*
		 * Turn off MC4_MISC thresholding banks on those models since
		 * they're not supported there.
		 */
		if (c->x86 == 0x15 &&
		    (c->x86_model >= 0x10 && c->x86_model <= 0x1f)) {
			int i;
			u64 hwcr;
			bool need_toggle;
			u32 msrs[] = {
				0x00000413, /* MC4_MISC0 */
				0xc0000408, /* MC4_MISC1 */
			};

			rdmsrl(MSR_K7_HWCR, hwcr);

			/* McStatusWrEn has to be set */
			need_toggle = !(hwcr & BIT(18));

			if (need_toggle)
				wrmsrl(MSR_K7_HWCR, hwcr | BIT(18));

			/* Clear CntP bit safely */
			for (i = 0; i < ARRAY_SIZE(msrs); i++)
				msr_clear_bit(msrs[i], 62);

			/* restore old settings */
			if (need_toggle)
				wrmsrl(MSR_K7_HWCR, hwcr);
		}
	}

	if (c->x86_vendor == X86_VENDOR_INTEL) {
		/*
		 * SDM documents that on family 6 bank 0 should not be written
		 * because it aliases to another special BIOS controlled
		 * register.
		 * But it's not aliased anymore on model 0x1a+
		 * Don't ignore bank 0 completely because there could be a
		 * valid event later, merely don't write CTL0.
		 */

		if (c->x86 == 6 && c->x86_model < 0x1A && cfg->banks > 0)
			mce_banks[0].init = 0;

		/*
		 * All newer Intel systems support MCE broadcasting. Enable
		 * synchronization with a one second timeout.
		 */
		if ((c->x86 > 6 || (c->x86 == 6 && c->x86_model >= 0xe)) &&
			cfg->monarch_timeout < 0)
			cfg->monarch_timeout = USEC_PER_SEC;

		/*
		 * There are also broken BIOSes on some Pentium M and
		 * earlier systems:
		 */
		if (c->x86 == 6 && c->x86_model <= 13 && cfg->bootlog < 0)
			cfg->bootlog = 0;

		if (c->x86 == 6 && c->x86_model == 45)
			quirk_no_way_out = quirk_sandybridge_ifu;
	}
	if (cfg->monarch_timeout < 0)
		cfg->monarch_timeout = 0;
	if (cfg->bootlog != 0)
		cfg->panic_timeout = 30;

	return 0;
}