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
typedef  int u32 ;
struct shmob_drm_device {int dummy; } ;
struct TYPE_4__ {TYPE_1__* dev; } ;
struct shmob_drm_crtc {TYPE_2__ crtc; } ;
struct TYPE_3__ {struct shmob_drm_device* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  LDCNT2R ; 
 int LDCNT2R_DO ; 
 int /*<<< orphan*/  LDDCKSTPR ; 
 int LDDCKSTPR_DCKSTP ; 
 int /*<<< orphan*/  LDPMR ; 
 int LDPMR_LPS ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int lcdc_read (struct shmob_drm_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lcdc_write (struct shmob_drm_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void shmob_drm_crtc_start_stop(struct shmob_drm_crtc *scrtc, bool start)
{
	struct shmob_drm_device *sdev = scrtc->crtc.dev->dev_private;
	u32 value;

	value = lcdc_read(sdev, LDCNT2R);
	if (start)
		lcdc_write(sdev, LDCNT2R, value | LDCNT2R_DO);
	else
		lcdc_write(sdev, LDCNT2R, value & ~LDCNT2R_DO);

	/* Wait until power is applied/stopped. */
	while (1) {
		value = lcdc_read(sdev, LDPMR) & LDPMR_LPS;
		if ((start && value) || (!start && !value))
			break;

		cpu_relax();
	}

	if (!start) {
		/* Stop the dot clock. */
		lcdc_write(sdev, LDDCKSTPR, LDDCKSTPR_DCKSTP);
	}
}