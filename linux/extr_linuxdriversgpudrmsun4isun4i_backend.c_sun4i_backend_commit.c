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
struct sunxi_engine {int /*<<< orphan*/  regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*) ; 
 int SUN4I_BACKEND_REGBUFFCTL_AUTOLOAD_DIS ; 
 int SUN4I_BACKEND_REGBUFFCTL_LOADCTL ; 
 int /*<<< orphan*/  SUN4I_BACKEND_REGBUFFCTL_REG ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void sun4i_backend_commit(struct sunxi_engine *engine)
{
	DRM_DEBUG_DRIVER("Committing changes\n");

	regmap_write(engine->regs, SUN4I_BACKEND_REGBUFFCTL_REG,
		     SUN4I_BACKEND_REGBUFFCTL_AUTOLOAD_DIS |
		     SUN4I_BACKEND_REGBUFFCTL_LOADCTL);
}