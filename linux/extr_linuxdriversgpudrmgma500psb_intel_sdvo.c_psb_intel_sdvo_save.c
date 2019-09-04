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
struct psb_intel_sdvo {int /*<<< orphan*/  sdvo_reg; int /*<<< orphan*/  saveSDVO; } ;
struct gma_encoder {int /*<<< orphan*/  base; } ;
struct drm_device {int dummy; } ;
struct drm_connector {struct drm_device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_READ (int /*<<< orphan*/ ) ; 
 struct gma_encoder* gma_attached_encoder (struct drm_connector*) ; 
 struct psb_intel_sdvo* to_psb_intel_sdvo (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void psb_intel_sdvo_save(struct drm_connector *connector)
{
	struct drm_device *dev = connector->dev;
	struct gma_encoder *gma_encoder = gma_attached_encoder(connector);
	struct psb_intel_sdvo *sdvo = to_psb_intel_sdvo(&gma_encoder->base);

	sdvo->saveSDVO = REG_READ(sdvo->sdvo_reg);
}