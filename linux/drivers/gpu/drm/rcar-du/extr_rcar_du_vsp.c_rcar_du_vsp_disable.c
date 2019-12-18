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
struct rcar_du_crtc {int /*<<< orphan*/  vsp_pipe; TYPE_1__* vsp; } ;
struct TYPE_2__ {int /*<<< orphan*/  vsp; } ;

/* Variables and functions */
 int /*<<< orphan*/  vsp1_du_setup_lif (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void rcar_du_vsp_disable(struct rcar_du_crtc *crtc)
{
	vsp1_du_setup_lif(crtc->vsp->vsp, crtc->vsp_pipe, NULL);
}