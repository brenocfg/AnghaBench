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
struct ipu_soc {int dummy; } ;
struct ipu_crtc {int /*<<< orphan*/  di; int /*<<< orphan*/  dc; TYPE_1__* dev; } ;
struct drm_crtc_state {int dummy; } ;
struct drm_crtc {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;

/* Variables and functions */
 struct ipu_soc* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipu_dc_enable (struct ipu_soc*) ; 
 int /*<<< orphan*/  ipu_dc_enable_channel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipu_di_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipu_prg_enable (struct ipu_soc*) ; 
 struct ipu_crtc* to_ipu_crtc (struct drm_crtc*) ; 

__attribute__((used)) static void ipu_crtc_atomic_enable(struct drm_crtc *crtc,
				   struct drm_crtc_state *old_state)
{
	struct ipu_crtc *ipu_crtc = to_ipu_crtc(crtc);
	struct ipu_soc *ipu = dev_get_drvdata(ipu_crtc->dev->parent);

	ipu_prg_enable(ipu);
	ipu_dc_enable(ipu);
	ipu_dc_enable_channel(ipu_crtc->dc);
	ipu_di_enable(ipu_crtc->di);
}