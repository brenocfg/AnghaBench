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
struct regmap {int dummy; } ;
struct drm_device {int /*<<< orphan*/  dev; } ;
struct drm_crtc_state {int dummy; } ;
struct drm_crtc {struct drm_device* dev; } ;
struct atmel_hlcdc_crtc {TYPE_2__* dc; } ;
struct TYPE_4__ {TYPE_1__* hlcdc; } ;
struct TYPE_3__ {int /*<<< orphan*/  sys_clk; struct regmap* regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATMEL_HLCDC_DIS ; 
 unsigned int ATMEL_HLCDC_DISP ; 
 unsigned int ATMEL_HLCDC_PIXEL_CLK ; 
 int /*<<< orphan*/  ATMEL_HLCDC_SR ; 
 unsigned int ATMEL_HLCDC_SYNC ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_relax () ; 
 struct atmel_hlcdc_crtc* drm_crtc_to_atmel_hlcdc_crtc (struct drm_crtc*) ; 
 int /*<<< orphan*/  drm_crtc_vblank_off (struct drm_crtc*) ; 
 int /*<<< orphan*/  pinctrl_pm_select_sleep_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_allow (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_read (struct regmap*,int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  regmap_write (struct regmap*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void atmel_hlcdc_crtc_atomic_disable(struct drm_crtc *c,
					    struct drm_crtc_state *old_state)
{
	struct drm_device *dev = c->dev;
	struct atmel_hlcdc_crtc *crtc = drm_crtc_to_atmel_hlcdc_crtc(c);
	struct regmap *regmap = crtc->dc->hlcdc->regmap;
	unsigned int status;

	drm_crtc_vblank_off(c);

	pm_runtime_get_sync(dev->dev);

	regmap_write(regmap, ATMEL_HLCDC_DIS, ATMEL_HLCDC_DISP);
	while (!regmap_read(regmap, ATMEL_HLCDC_SR, &status) &&
	       (status & ATMEL_HLCDC_DISP))
		cpu_relax();

	regmap_write(regmap, ATMEL_HLCDC_DIS, ATMEL_HLCDC_SYNC);
	while (!regmap_read(regmap, ATMEL_HLCDC_SR, &status) &&
	       (status & ATMEL_HLCDC_SYNC))
		cpu_relax();

	regmap_write(regmap, ATMEL_HLCDC_DIS, ATMEL_HLCDC_PIXEL_CLK);
	while (!regmap_read(regmap, ATMEL_HLCDC_SR, &status) &&
	       (status & ATMEL_HLCDC_PIXEL_CLK))
		cpu_relax();

	clk_disable_unprepare(crtc->dc->hlcdc->sys_clk);
	pinctrl_pm_select_sleep_state(dev->dev);

	pm_runtime_allow(dev->dev);

	pm_runtime_put_sync(dev->dev);
}