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
struct rcar_du_crtc {int /*<<< orphan*/  writeback; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_writeback_signal_completion (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void rcar_du_writeback_complete(struct rcar_du_crtc *rcrtc)
{
	drm_writeback_signal_completion(&rcrtc->writeback, 0);
}