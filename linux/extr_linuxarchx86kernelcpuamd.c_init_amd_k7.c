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
struct cpuinfo_x86 {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static void init_amd_k7(struct cpuinfo_x86 *c)
{
#ifdef CONFIG_X86_32
	u32 l, h;

	/*
	 * Bit 15 of Athlon specific MSR 15, needs to be 0
	 * to enable SSE on Palomino/Morgan/Barton CPU's.
	 * If the BIOS didn't enable it already, enable it here.
	 */
	if (c->x86_model >= 6 && c->x86_model <= 10) {
		if (!cpu_has(c, X86_FEATURE_XMM)) {
			pr_info("Enabling disabled K7/SSE Support.\n");
			msr_clear_bit(MSR_K7_HWCR, 15);
			set_cpu_cap(c, X86_FEATURE_XMM);
		}
	}

	/*
	 * It's been determined by AMD that Athlons since model 8 stepping 1
	 * are more robust with CLK_CTL set to 200xxxxx instead of 600xxxxx
	 * As per AMD technical note 27212 0.2
	 */
	if ((c->x86_model == 8 && c->x86_stepping >= 1) || (c->x86_model > 8)) {
		rdmsr(MSR_K7_CLK_CTL, l, h);
		if ((l & 0xfff00000) != 0x20000000) {
			pr_info("CPU: CLK_CTL MSR was %x. Reprogramming to %x\n",
				l, ((l & 0x000fffff)|0x20000000));
			wrmsr(MSR_K7_CLK_CTL, (l & 0x000fffff)|0x20000000, h);
		}
	}

	/* calling is from identify_secondary_cpu() ? */
	if (!c->cpu_index)
		return;

	/*
	 * Certain Athlons might work (for various values of 'work') in SMP
	 * but they are not certified as MP capable.
	 */
	/* Athlon 660/661 is valid. */
	if ((c->x86_model == 6) && ((c->x86_stepping == 0) ||
	    (c->x86_stepping == 1)))
		return;

	/* Duron 670 is valid */
	if ((c->x86_model == 7) && (c->x86_stepping == 0))
		return;

	/*
	 * Athlon 662, Duron 671, and Athlon >model 7 have capability
	 * bit. It's worth noting that the A5 stepping (662) of some
	 * Athlon XP's have the MP bit set.
	 * See http://www.heise.de/newsticker/data/jow-18.10.01-000 for
	 * more.
	 */
	if (((c->x86_model == 6) && (c->x86_stepping >= 2)) ||
	    ((c->x86_model == 7) && (c->x86_stepping >= 1)) ||
	     (c->x86_model > 7))
		if (cpu_has(c, X86_FEATURE_MP))
			return;

	/* If we get here, not a certified SMP capable AMD system. */

	/*
	 * Don't taint if we are running SMP kernel on a single non-MP
	 * approved Athlon
	 */
	WARN_ONCE(1, "WARNING: This combination of AMD"
		" processors is not suitable for SMP.\n");
	add_taint(TAINT_CPU_OUT_OF_SPEC, LOCKDEP_NOW_UNRELIABLE);
#endif
}