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
struct sti_tvout {int /*<<< orphan*/  dvo; int /*<<< orphan*/  hda; int /*<<< orphan*/  hdmi; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  sti_tvout_create_dvo_encoder (struct drm_device*,struct sti_tvout*) ; 
 int /*<<< orphan*/  sti_tvout_create_hda_encoder (struct drm_device*,struct sti_tvout*) ; 
 int /*<<< orphan*/  sti_tvout_create_hdmi_encoder (struct drm_device*,struct sti_tvout*) ; 

__attribute__((used)) static void sti_tvout_create_encoders(struct drm_device *dev,
		struct sti_tvout *tvout)
{
	tvout->hdmi = sti_tvout_create_hdmi_encoder(dev, tvout);
	tvout->hda = sti_tvout_create_hda_encoder(dev, tvout);
	tvout->dvo = sti_tvout_create_dvo_encoder(dev, tvout);
}