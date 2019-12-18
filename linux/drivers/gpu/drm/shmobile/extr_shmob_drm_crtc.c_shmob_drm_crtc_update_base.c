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
struct shmob_drm_device {int dummy; } ;
struct drm_crtc {int /*<<< orphan*/  y; int /*<<< orphan*/  x; TYPE_2__* dev; } ;
struct shmob_drm_crtc {int /*<<< orphan*/ * dma; TYPE_1__* format; struct drm_crtc crtc; } ;
struct TYPE_4__ {struct shmob_drm_device* dev_private; } ;
struct TYPE_3__ {scalar_t__ yuv; } ;

/* Variables and functions */
 int /*<<< orphan*/  LDRCNTR ; 
 int LDRCNTR_MRS ; 
 int /*<<< orphan*/  LDSA1R ; 
 int /*<<< orphan*/  LDSA2R ; 
 int lcdc_read (struct shmob_drm_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lcdc_write (struct shmob_drm_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  lcdc_write_mirror (struct shmob_drm_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shmob_drm_crtc_compute_base (struct shmob_drm_crtc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void shmob_drm_crtc_update_base(struct shmob_drm_crtc *scrtc)
{
	struct drm_crtc *crtc = &scrtc->crtc;
	struct shmob_drm_device *sdev = crtc->dev->dev_private;

	shmob_drm_crtc_compute_base(scrtc, crtc->x, crtc->y);

	lcdc_write_mirror(sdev, LDSA1R, scrtc->dma[0]);
	if (scrtc->format->yuv)
		lcdc_write_mirror(sdev, LDSA2R, scrtc->dma[1]);

	lcdc_write(sdev, LDRCNTR, lcdc_read(sdev, LDRCNTR) ^ LDRCNTR_MRS);
}