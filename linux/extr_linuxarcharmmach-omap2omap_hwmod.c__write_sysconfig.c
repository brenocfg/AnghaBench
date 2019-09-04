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
struct omap_hwmod {TYPE_2__* class; int /*<<< orphan*/  _sysc_cache; int /*<<< orphan*/  name; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* lock ) (struct omap_hwmod*) ;TYPE_1__* sysc; int /*<<< orphan*/  (* unlock ) (struct omap_hwmod*) ;} ;
struct TYPE_3__ {int /*<<< orphan*/  sysc_offs; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap_hwmod_write (int /*<<< orphan*/ ,struct omap_hwmod*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct omap_hwmod*) ; 
 int /*<<< orphan*/  stub2 (struct omap_hwmod*) ; 

__attribute__((used)) static void _write_sysconfig(u32 v, struct omap_hwmod *oh)
{
	if (!oh->class->sysc) {
		WARN(1, "omap_hwmod: %s: cannot write OCP_SYSCONFIG: not defined on hwmod's class\n", oh->name);
		return;
	}

	/* XXX ensure module interface clock is up */

	/* Module might have lost context, always update cache and register */
	oh->_sysc_cache = v;

	/*
	 * Some IP blocks (such as RTC) require unlocking of IP before
	 * accessing its registers. If a function pointer is present
	 * to unlock, then call it before accessing sysconfig and
	 * call lock after writing sysconfig.
	 */
	if (oh->class->unlock)
		oh->class->unlock(oh);

	omap_hwmod_write(v, oh, oh->class->sysc->sysc_offs);

	if (oh->class->lock)
		oh->class->lock(oh);
}