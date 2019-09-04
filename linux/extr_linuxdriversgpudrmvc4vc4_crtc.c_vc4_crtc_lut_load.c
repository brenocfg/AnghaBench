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
typedef  size_t u32 ;
struct vc4_dev {int dummy; } ;
struct vc4_crtc {int channel; int* lut_r; int* lut_g; int* lut_b; } ;
struct drm_device {int dummy; } ;
struct drm_crtc {int gamma_size; struct drm_device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  HVS_WRITE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SCALER_GAMADDR ; 
 int SCALER_GAMADDR_AUTOINC ; 
 int /*<<< orphan*/  SCALER_GAMDATA ; 
 struct vc4_crtc* to_vc4_crtc (struct drm_crtc*) ; 
 struct vc4_dev* to_vc4_dev (struct drm_device*) ; 

__attribute__((used)) static void
vc4_crtc_lut_load(struct drm_crtc *crtc)
{
	struct drm_device *dev = crtc->dev;
	struct vc4_dev *vc4 = to_vc4_dev(dev);
	struct vc4_crtc *vc4_crtc = to_vc4_crtc(crtc);
	u32 i;

	/* The LUT memory is laid out with each HVS channel in order,
	 * each of which takes 256 writes for R, 256 for G, then 256
	 * for B.
	 */
	HVS_WRITE(SCALER_GAMADDR,
		  SCALER_GAMADDR_AUTOINC |
		  (vc4_crtc->channel * 3 * crtc->gamma_size));

	for (i = 0; i < crtc->gamma_size; i++)
		HVS_WRITE(SCALER_GAMDATA, vc4_crtc->lut_r[i]);
	for (i = 0; i < crtc->gamma_size; i++)
		HVS_WRITE(SCALER_GAMDATA, vc4_crtc->lut_g[i]);
	for (i = 0; i < crtc->gamma_size; i++)
		HVS_WRITE(SCALER_GAMDATA, vc4_crtc->lut_b[i]);
}