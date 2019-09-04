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
typedef  int /*<<< orphan*/  u32 ;
struct omap_hwmod {scalar_t__ _state; int flags; int /*<<< orphan*/  name; TYPE_2__* class; int /*<<< orphan*/  _sysc_cache; } ;
struct TYPE_4__ {TYPE_1__* sysc; } ;
struct TYPE_3__ {int sysc_flags; scalar_t__ srst_udelay; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 int ETIMEDOUT ; 
 int HWMOD_CONTROL_OPT_CLKS_IN_RESET ; 
 int MAX_MODULE_SOFTRESET_WAIT ; 
 int SYSC_HAS_SOFTRESET ; 
 scalar_t__ _HWMOD_STATE_ENABLED ; 
 int _clear_softreset (struct omap_hwmod*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _disable_optional_clocks (struct omap_hwmod*) ; 
 int /*<<< orphan*/  _enable_optional_clocks (struct omap_hwmod*) ; 
 int _set_softreset (struct omap_hwmod*,int /*<<< orphan*/ *) ; 
 int _wait_softreset_complete (struct omap_hwmod*) ; 
 int /*<<< orphan*/  _write_sysconfig (int /*<<< orphan*/ ,struct omap_hwmod*) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  udelay (scalar_t__) ; 

__attribute__((used)) static int _ocp_softreset(struct omap_hwmod *oh)
{
	u32 v;
	int c = 0;
	int ret = 0;

	if (!oh->class->sysc ||
	    !(oh->class->sysc->sysc_flags & SYSC_HAS_SOFTRESET))
		return -ENOENT;

	/* clocks must be on for this operation */
	if (oh->_state != _HWMOD_STATE_ENABLED) {
		pr_warn("omap_hwmod: %s: reset can only be entered from enabled state\n",
			oh->name);
		return -EINVAL;
	}

	/* For some modules, all optionnal clocks need to be enabled as well */
	if (oh->flags & HWMOD_CONTROL_OPT_CLKS_IN_RESET)
		_enable_optional_clocks(oh);

	pr_debug("omap_hwmod: %s: resetting via OCP SOFTRESET\n", oh->name);

	v = oh->_sysc_cache;
	ret = _set_softreset(oh, &v);
	if (ret)
		goto dis_opt_clks;

	_write_sysconfig(v, oh);

	if (oh->class->sysc->srst_udelay)
		udelay(oh->class->sysc->srst_udelay);

	c = _wait_softreset_complete(oh);
	if (c == MAX_MODULE_SOFTRESET_WAIT) {
		pr_warn("omap_hwmod: %s: softreset failed (waited %d usec)\n",
			oh->name, MAX_MODULE_SOFTRESET_WAIT);
		ret = -ETIMEDOUT;
		goto dis_opt_clks;
	} else {
		pr_debug("omap_hwmod: %s: softreset in %d usec\n", oh->name, c);
	}

	ret = _clear_softreset(oh, &v);
	if (ret)
		goto dis_opt_clks;

	_write_sysconfig(v, oh);

	/*
	 * XXX add _HWMOD_STATE_WEDGED for modules that don't come back from
	 * _wait_target_ready() or _reset()
	 */

dis_opt_clks:
	if (oh->flags & HWMOD_CONTROL_OPT_CLKS_IN_RESET)
		_disable_optional_clocks(oh);

	return ret;
}