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
typedef  int /*<<< orphan*/  u16 ;
struct drm_device {struct cirrus_device* dev_private; } ;
struct drm_crtc {int gamma_size; int /*<<< orphan*/ * gamma_store; int /*<<< orphan*/  enabled; struct drm_device* dev; } ;
struct cirrus_device {int dummy; } ;

/* Variables and functions */
 int CIRRUS_LUT_SIZE ; 
 int /*<<< orphan*/  PALETTE_DATA ; 
 int /*<<< orphan*/  PALETTE_INDEX ; 
 int /*<<< orphan*/  WREG8 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void cirrus_crtc_load_lut(struct drm_crtc *crtc)
{
	struct drm_device *dev = crtc->dev;
	struct cirrus_device *cdev = dev->dev_private;
	u16 *r, *g, *b;
	int i;

	if (!crtc->enabled)
		return;

	r = crtc->gamma_store;
	g = r + crtc->gamma_size;
	b = g + crtc->gamma_size;

	for (i = 0; i < CIRRUS_LUT_SIZE; i++) {
		/* VGA registers */
		WREG8(PALETTE_INDEX, i);
		WREG8(PALETTE_DATA, *r++ >> 8);
		WREG8(PALETTE_DATA, *g++ >> 8);
		WREG8(PALETTE_DATA, *b++ >> 8);
	}
}