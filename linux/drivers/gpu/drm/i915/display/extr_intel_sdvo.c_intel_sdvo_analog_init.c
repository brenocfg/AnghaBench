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
struct drm_connector {int /*<<< orphan*/  connector_type; } ;
struct intel_connector {int /*<<< orphan*/  polled; struct drm_connector base; } ;
struct intel_sdvo_connector {int /*<<< orphan*/  output_flag; struct intel_connector base; } ;
struct drm_encoder {int /*<<< orphan*/  encoder_type; } ;
struct TYPE_2__ {struct drm_encoder base; } ;
struct intel_sdvo {int /*<<< orphan*/  controlled_output; TYPE_1__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_CONNECTOR_POLL_CONNECT ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int) ; 
 int /*<<< orphan*/  DRM_MODE_CONNECTOR_VGA ; 
 int /*<<< orphan*/  DRM_MODE_ENCODER_DAC ; 
 int /*<<< orphan*/  SDVO_OUTPUT_RGB0 ; 
 int /*<<< orphan*/  SDVO_OUTPUT_RGB1 ; 
 struct intel_sdvo_connector* intel_sdvo_connector_alloc () ; 
 scalar_t__ intel_sdvo_connector_init (struct intel_sdvo_connector*,struct intel_sdvo*) ; 
 int /*<<< orphan*/  kfree (struct intel_sdvo_connector*) ; 

__attribute__((used)) static bool
intel_sdvo_analog_init(struct intel_sdvo *intel_sdvo, int device)
{
	struct drm_encoder *encoder = &intel_sdvo->base.base;
	struct drm_connector *connector;
	struct intel_connector *intel_connector;
	struct intel_sdvo_connector *intel_sdvo_connector;

	DRM_DEBUG_KMS("initialising analog device %d\n", device);

	intel_sdvo_connector = intel_sdvo_connector_alloc();
	if (!intel_sdvo_connector)
		return false;

	intel_connector = &intel_sdvo_connector->base;
	connector = &intel_connector->base;
	intel_connector->polled = DRM_CONNECTOR_POLL_CONNECT;
	encoder->encoder_type = DRM_MODE_ENCODER_DAC;
	connector->connector_type = DRM_MODE_CONNECTOR_VGA;

	if (device == 0) {
		intel_sdvo->controlled_output |= SDVO_OUTPUT_RGB0;
		intel_sdvo_connector->output_flag = SDVO_OUTPUT_RGB0;
	} else if (device == 1) {
		intel_sdvo->controlled_output |= SDVO_OUTPUT_RGB1;
		intel_sdvo_connector->output_flag = SDVO_OUTPUT_RGB1;
	}

	if (intel_sdvo_connector_init(intel_sdvo_connector, intel_sdvo) < 0) {
		kfree(intel_sdvo_connector);
		return false;
	}

	return true;
}