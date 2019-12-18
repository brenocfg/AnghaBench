#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  status; } ;
struct sti_hqvdp {int vtg_registered; TYPE_1__ plane; int /*<<< orphan*/  clk_pix_main; scalar_t__ regs; int /*<<< orphan*/  vtg_nb; int /*<<< orphan*/  vtg; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*,...) ; 
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 scalar_t__ HQVDP_MBX_INFO_XP70 ; 
 scalar_t__ HQVDP_MBX_NEXT_CMD ; 
 int INFO_XP70_FW_READY ; 
 int /*<<< orphan*/  POLL_DELAY_MS ; 
 int POLL_MAX_ATTEMPT ; 
 int /*<<< orphan*/  STI_PLANE_DISABLED ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  sti_plane_to_str (TYPE_1__*) ; 
 scalar_t__ sti_vtg_unregister_client (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void sti_hqvdp_disable(struct sti_hqvdp *hqvdp)
{
	int i;

	DRM_DEBUG_DRIVER("%s\n", sti_plane_to_str(&hqvdp->plane));

	/* Unregister VTG Vsync callback */
	if (sti_vtg_unregister_client(hqvdp->vtg, &hqvdp->vtg_nb))
		DRM_DEBUG_DRIVER("Warning: cannot unregister VTG notifier\n");

	/* Set next cmd to NULL */
	writel(0, hqvdp->regs + HQVDP_MBX_NEXT_CMD);

	for (i = 0; i < POLL_MAX_ATTEMPT; i++) {
		if (readl(hqvdp->regs + HQVDP_MBX_INFO_XP70)
				& INFO_XP70_FW_READY)
			break;
		msleep(POLL_DELAY_MS);
	}

	/* VTG can stop now */
	clk_disable_unprepare(hqvdp->clk_pix_main);

	if (i == POLL_MAX_ATTEMPT)
		DRM_ERROR("XP70 could not revert to idle\n");

	hqvdp->plane.status = STI_PLANE_DISABLED;
	hqvdp->vtg_registered = false;
}