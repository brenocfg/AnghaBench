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
typedef  int uint64_t ;
struct clock_event_device {int mult; int shift; } ;

/* Variables and functions */
 int /*<<< orphan*/  HPET_COUNTER ; 
 unsigned int HPET_TN_32BIT ; 
 unsigned int HPET_TN_ENABLE ; 
 unsigned int HPET_TN_PERIODIC ; 
 unsigned int HPET_TN_SETVAL ; 
 int /*<<< orphan*/  HPET_Tn_CFG (int) ; 
 int /*<<< orphan*/  HPET_Tn_CMP (int) ; 
 int HZ ; 
 int NSEC_PER_SEC ; 
 int /*<<< orphan*/  hpet_print_config () ; 
 unsigned int hpet_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hpet_start_counter () ; 
 int /*<<< orphan*/  hpet_stop_counter () ; 
 int /*<<< orphan*/  hpet_writel (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int hpet_set_periodic(struct clock_event_device *evt, int timer)
{
	unsigned int cfg, cmp, now;
	uint64_t delta;

	hpet_stop_counter();
	delta = ((uint64_t)(NSEC_PER_SEC / HZ)) * evt->mult;
	delta >>= evt->shift;
	now = hpet_readl(HPET_COUNTER);
	cmp = now + (unsigned int)delta;
	cfg = hpet_readl(HPET_Tn_CFG(timer));
	cfg |= HPET_TN_ENABLE | HPET_TN_PERIODIC | HPET_TN_SETVAL |
	       HPET_TN_32BIT;
	hpet_writel(cfg, HPET_Tn_CFG(timer));
	hpet_writel(cmp, HPET_Tn_CMP(timer));
	udelay(1);
	/*
	 * HPET on AMD 81xx needs a second write (with HPET_TN_SETVAL
	 * cleared) to T0_CMP to set the period. The HPET_TN_SETVAL
	 * bit is automatically cleared after the first write.
	 * (See AMD-8111 HyperTransport I/O Hub Data Sheet,
	 * Publication # 24674)
	 */
	hpet_writel((unsigned int)delta, HPET_Tn_CMP(timer));
	hpet_start_counter();
	hpet_print_config();

	return 0;
}