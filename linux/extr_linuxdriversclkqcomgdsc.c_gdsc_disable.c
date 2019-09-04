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
struct generic_pm_domain {int dummy; } ;
struct gdsc {scalar_t__ pwrsts; int flags; } ;

/* Variables and functions */
 int CLAMP_IO ; 
 int /*<<< orphan*/  GDSC_OFF ; 
 int /*<<< orphan*/  GDSC_ON ; 
 int HW_CTRL ; 
 int PWRSTS_OFF ; 
 scalar_t__ PWRSTS_ON ; 
 struct gdsc* domain_to_gdsc (struct generic_pm_domain*) ; 
 int /*<<< orphan*/  gdsc_assert_clamp_io (struct gdsc*) ; 
 int gdsc_assert_reset (struct gdsc*) ; 
 int /*<<< orphan*/  gdsc_clear_mem_on (struct gdsc*) ; 
 int gdsc_hwctrl (struct gdsc*,int) ; 
 int gdsc_poll_status (struct gdsc*,int /*<<< orphan*/ ) ; 
 int gdsc_toggle_logic (struct gdsc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int gdsc_disable(struct generic_pm_domain *domain)
{
	struct gdsc *sc = domain_to_gdsc(domain);
	int ret;

	if (sc->pwrsts == PWRSTS_ON)
		return gdsc_assert_reset(sc);

	/* Turn off HW trigger mode if supported */
	if (sc->flags & HW_CTRL) {
		ret = gdsc_hwctrl(sc, false);
		if (ret < 0)
			return ret;
		/*
		 * Wait for the GDSC to go through a power down and
		 * up cycle.  In case we end up polling status
		 * bits for the gdsc before the power cycle is completed
		 * it might read an 'on' status wrongly.
		 */
		udelay(1);

		ret = gdsc_poll_status(sc, GDSC_ON);
		if (ret)
			return ret;
	}

	if (sc->pwrsts & PWRSTS_OFF)
		gdsc_clear_mem_on(sc);

	ret = gdsc_toggle_logic(sc, GDSC_OFF);
	if (ret)
		return ret;

	if (sc->flags & CLAMP_IO)
		gdsc_assert_clamp_io(sc);

	return 0;
}