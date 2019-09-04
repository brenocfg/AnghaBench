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
struct drm_crtc {int dummy; } ;
struct atmel_hlcdc_crtc {TYPE_2__* dc; } ;
struct TYPE_4__ {TYPE_1__* hlcdc; } ;
struct TYPE_3__ {struct regmap* regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATMEL_HLCDC_IDR ; 
 int /*<<< orphan*/  ATMEL_HLCDC_SOF ; 
 struct atmel_hlcdc_crtc* drm_crtc_to_atmel_hlcdc_crtc (struct drm_crtc*) ; 
 int /*<<< orphan*/  regmap_write (struct regmap*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void atmel_hlcdc_crtc_disable_vblank(struct drm_crtc *c)
{
	struct atmel_hlcdc_crtc *crtc = drm_crtc_to_atmel_hlcdc_crtc(c);
	struct regmap *regmap = crtc->dc->hlcdc->regmap;

	regmap_write(regmap, ATMEL_HLCDC_IDR, ATMEL_HLCDC_SOF);
}