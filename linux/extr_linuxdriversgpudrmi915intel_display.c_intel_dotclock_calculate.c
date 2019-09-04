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
struct intel_link_m_n {int /*<<< orphan*/  link_n; int /*<<< orphan*/  link_m; } ;

/* Variables and functions */
 int div_u64 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mul_u32_u32 (int /*<<< orphan*/ ,int) ; 

int intel_dotclock_calculate(int link_freq,
			     const struct intel_link_m_n *m_n)
{
	/*
	 * The calculation for the data clock is:
	 * pixel_clock = ((m/n)*(link_clock * nr_lanes))/bpp
	 * But we want to avoid losing precison if possible, so:
	 * pixel_clock = ((m * link_clock * nr_lanes)/(n*bpp))
	 *
	 * and the link clock is simpler:
	 * link_clock = (m * link_clock) / n
	 */

	if (!m_n->link_n)
		return 0;

	return div_u64(mul_u32_u32(m_n->link_m, link_freq), m_n->link_n);
}