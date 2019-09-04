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
typedef  int u32 ;
struct sunxi_engine {int /*<<< orphan*/  regs; } ;
struct drm_crtc_state {int dummy; } ;

/* Variables and functions */
 int SUN4I_BACKEND_REGBUFFCTL_LOADCTL ; 
 int /*<<< orphan*/  SUN4I_BACKEND_REGBUFFCTL_REG ; 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_read_poll_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int) ; 

__attribute__((used)) static void sun4i_backend_atomic_begin(struct sunxi_engine *engine,
				       struct drm_crtc_state *old_state)
{
	u32 val;

	WARN_ON(regmap_read_poll_timeout(engine->regs,
					 SUN4I_BACKEND_REGBUFFCTL_REG,
					 val, !(val & SUN4I_BACKEND_REGBUFFCTL_LOADCTL),
					 100, 50000));
}