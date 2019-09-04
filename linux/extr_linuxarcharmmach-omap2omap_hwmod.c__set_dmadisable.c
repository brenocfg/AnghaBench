#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct omap_hwmod {scalar_t__ _state; int _sysc_cache; TYPE_3__* class; int /*<<< orphan*/  name; } ;
struct TYPE_6__ {TYPE_2__* sysc; } ;
struct TYPE_5__ {int sysc_flags; TYPE_1__* sysc_fields; } ;
struct TYPE_4__ {int dmadisable_shift; } ;

/* Variables and functions */
 int EINVAL ; 
 int SYSC_HAS_DMADISABLE ; 
 int /*<<< orphan*/  WARN (int,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ _HWMOD_STATE_ENABLED ; 
 int /*<<< orphan*/  _write_sysconfig (int,struct omap_hwmod*) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int _set_dmadisable(struct omap_hwmod *oh)
{
	u32 v;
	u32 dmadisable_mask;

	if (!oh->class->sysc ||
	    !(oh->class->sysc->sysc_flags & SYSC_HAS_DMADISABLE))
		return -EINVAL;

	if (!oh->class->sysc->sysc_fields) {
		WARN(1, "omap_hwmod: %s: offset struct for sysconfig not provided in class\n", oh->name);
		return -EINVAL;
	}

	/* clocks must be on for this operation */
	if (oh->_state != _HWMOD_STATE_ENABLED) {
		pr_warn("omap_hwmod: %s: dma can be disabled only from enabled state\n", oh->name);
		return -EINVAL;
	}

	pr_debug("omap_hwmod: %s: setting DMADISABLE\n", oh->name);

	v = oh->_sysc_cache;
	dmadisable_mask =
		(0x1 << oh->class->sysc->sysc_fields->dmadisable_shift);
	v |= dmadisable_mask;
	_write_sysconfig(v, oh);

	return 0;
}