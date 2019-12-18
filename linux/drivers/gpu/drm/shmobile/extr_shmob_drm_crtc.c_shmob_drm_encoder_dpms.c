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
struct shmob_drm_encoder {int dpms; } ;
struct shmob_drm_connector {int dummy; } ;
struct shmob_drm_device {struct shmob_drm_connector connector; } ;
struct drm_encoder {TYPE_1__* dev; } ;
struct TYPE_2__ {struct shmob_drm_device* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  shmob_drm_backlight_dpms (struct shmob_drm_connector*,int) ; 
 struct shmob_drm_encoder* to_shmob_encoder (struct drm_encoder*) ; 

__attribute__((used)) static void shmob_drm_encoder_dpms(struct drm_encoder *encoder, int mode)
{
	struct shmob_drm_encoder *senc = to_shmob_encoder(encoder);
	struct shmob_drm_device *sdev = encoder->dev->dev_private;
	struct shmob_drm_connector *scon = &sdev->connector;

	if (senc->dpms == mode)
		return;

	shmob_drm_backlight_dpms(scon, mode);

	senc->dpms = mode;
}