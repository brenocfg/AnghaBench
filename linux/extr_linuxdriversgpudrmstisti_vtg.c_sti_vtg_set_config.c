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
struct sti_vtg {int /*<<< orphan*/  sync_params; } ;
struct drm_display_mode {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  VTG_MODE_MASTER ; 
 int /*<<< orphan*/  vtg_enable_irq (struct sti_vtg*) ; 
 int /*<<< orphan*/  vtg_reset (struct sti_vtg*) ; 
 int /*<<< orphan*/  vtg_set_mode (struct sti_vtg*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct drm_display_mode const*) ; 

void sti_vtg_set_config(struct sti_vtg *vtg,
		const struct drm_display_mode *mode)
{
	/* write configuration */
	vtg_set_mode(vtg, VTG_MODE_MASTER, vtg->sync_params, mode);

	vtg_reset(vtg);

	vtg_enable_irq(vtg);
}