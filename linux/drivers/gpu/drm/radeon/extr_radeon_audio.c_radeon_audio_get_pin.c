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
struct radeon_encoder {TYPE_2__* audio; } ;
struct radeon_device {int dummy; } ;
struct r600_audio_pin {int dummy; } ;
struct drm_encoder {TYPE_1__* dev; } ;
struct TYPE_4__ {struct r600_audio_pin* (* get_pin ) (struct radeon_device*) ;} ;
struct TYPE_3__ {struct radeon_device* dev_private; } ;

/* Variables and functions */
 struct r600_audio_pin* stub1 (struct radeon_device*) ; 
 struct radeon_encoder* to_radeon_encoder (struct drm_encoder*) ; 

struct r600_audio_pin* radeon_audio_get_pin(struct drm_encoder *encoder)
{
	struct radeon_device *rdev = encoder->dev->dev_private;
	struct radeon_encoder *radeon_encoder = to_radeon_encoder(encoder);

	if (radeon_encoder->audio && radeon_encoder->audio->get_pin)
		return radeon_encoder->audio->get_pin(rdev);

	return NULL;
}