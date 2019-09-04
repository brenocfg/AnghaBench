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
typedef  int /*<<< orphan*/  u32 ;
struct msm_drm_private {unsigned int num_crtcs; struct drm_crtc** crtcs; } ;
struct drm_encoder {int dummy; } ;
struct drm_device {struct msm_drm_private* dev_private; } ;
struct drm_crtc {int dummy; } ;

/* Variables and functions */
 struct drm_encoder* get_encoder_from_crtc (struct drm_crtc*) ; 
 int /*<<< orphan*/  mdp5_encoder_get_framecount (struct drm_encoder*) ; 

__attribute__((used)) static u32 mdp5_get_vblank_counter(struct drm_device *dev, unsigned int pipe)
{
	struct msm_drm_private *priv = dev->dev_private;
	struct drm_crtc *crtc;
	struct drm_encoder *encoder;

	if (pipe >= priv->num_crtcs)
		return 0;

	crtc = priv->crtcs[pipe];
	if (!crtc)
		return 0;

	encoder = get_encoder_from_crtc(crtc);
	if (!encoder)
		return 0;

	return mdp5_encoder_get_framecount(encoder);
}