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
struct nv04_crtc_reg {int /*<<< orphan*/ * CRTC; } ;
struct drm_crtc {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  index; } ;

/* Variables and functions */
 int /*<<< orphan*/  NVWriteVgaCrtc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 TYPE_1__* nouveau_crtc (struct drm_crtc*) ; 

__attribute__((used)) static void
crtc_wr_cio_state(struct drm_crtc *crtc, struct nv04_crtc_reg *crtcstate, int index)
{
	NVWriteVgaCrtc(crtc->dev, nouveau_crtc(crtc)->index, index,
		       crtcstate->CRTC[index]);
}