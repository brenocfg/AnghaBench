#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_11__ {int possible_crtcs; } ;
struct intel_encoder {int crtc_mask; TYPE_5__ base; scalar_t__ cloneable; int /*<<< orphan*/  port; int /*<<< orphan*/  power_domain; int /*<<< orphan*/  type; int /*<<< orphan*/  get_hw_state; int /*<<< orphan*/  disable; int /*<<< orphan*/  enable; int /*<<< orphan*/  pre_enable; int /*<<< orphan*/  get_config; int /*<<< orphan*/  compute_config; } ;
struct intel_tv {int /*<<< orphan*/  type; struct intel_encoder base; } ;
struct drm_connector {int interlace_allowed; int doublescan_allowed; int /*<<< orphan*/  base; struct drm_connector_state* state; } ;
struct intel_connector {int /*<<< orphan*/  get_hw_state; int /*<<< orphan*/  polled; struct drm_connector base; } ;
struct TYPE_7__ {int /*<<< orphan*/  tv_bottom_margin_property; int /*<<< orphan*/  tv_right_margin_property; int /*<<< orphan*/  tv_top_margin_property; int /*<<< orphan*/  tv_left_margin_property; int /*<<< orphan*/  tv_mode_property; } ;
struct drm_device {TYPE_1__ mode_config; } ;
struct drm_i915_private {struct drm_device drm; } ;
struct TYPE_8__ {int left; int top; int right; int bottom; } ;
struct TYPE_9__ {int mode; TYPE_2__ margins; } ;
struct drm_connector_state {TYPE_3__ tv; } ;
struct TYPE_10__ {int oversample; char* name; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_4__*) ; 
 int /*<<< orphan*/  DRM_CONNECTOR_POLL_CONNECT ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*) ; 
 int /*<<< orphan*/  DRM_MODE_CONNECTOR_SVIDEO ; 
 int /*<<< orphan*/  DRM_MODE_CONNECTOR_Unknown ; 
 int /*<<< orphan*/  DRM_MODE_ENCODER_TVDAC ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  INTEL_OUTPUT_TVOUT ; 
 scalar_t__ IS_GEN (struct drm_i915_private*,int) ; 
 int /*<<< orphan*/  PORT_NONE ; 
 int /*<<< orphan*/  POWER_DOMAIN_PORT_OTHER ; 
 int TVDAC_STATE_CHG_EN ; 
 int /*<<< orphan*/  TV_CTL ; 
 int /*<<< orphan*/  TV_DAC ; 
 int TV_FUSE_STATE_DISABLED ; 
 int TV_FUSE_STATE_MASK ; 
 int /*<<< orphan*/  drm_connector_helper_add (struct drm_connector*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_connector_init (struct drm_device*,struct drm_connector*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_encoder_init (struct drm_device*,TYPE_5__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  drm_mode_create_tv_properties (struct drm_device*,int,char const**) ; 
 int /*<<< orphan*/  drm_object_attach_property (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  intel_bios_is_tv_present (struct drm_i915_private*) ; 
 struct intel_connector* intel_connector_alloc () ; 
 int /*<<< orphan*/  intel_connector_attach_encoder (struct intel_connector*,struct intel_encoder*) ; 
 int /*<<< orphan*/  intel_connector_get_hw_state ; 
 int /*<<< orphan*/  intel_disable_tv ; 
 int /*<<< orphan*/  intel_enable_tv ; 
 int /*<<< orphan*/  intel_tv_compute_config ; 
 int /*<<< orphan*/  intel_tv_connector_funcs ; 
 int /*<<< orphan*/  intel_tv_connector_helper_funcs ; 
 int /*<<< orphan*/  intel_tv_enc_funcs ; 
 int /*<<< orphan*/  intel_tv_get_config ; 
 int /*<<< orphan*/  intel_tv_get_hw_state ; 
 int /*<<< orphan*/  intel_tv_pre_enable ; 
 int /*<<< orphan*/  kfree (struct intel_tv*) ; 
 struct intel_tv* kzalloc (int,int /*<<< orphan*/ ) ; 
 TYPE_4__* tv_modes ; 

void
intel_tv_init(struct drm_i915_private *dev_priv)
{
	struct drm_device *dev = &dev_priv->drm;
	struct drm_connector *connector;
	struct intel_tv *intel_tv;
	struct intel_encoder *intel_encoder;
	struct intel_connector *intel_connector;
	u32 tv_dac_on, tv_dac_off, save_tv_dac;
	const char *tv_format_names[ARRAY_SIZE(tv_modes)];
	int i, initial_mode = 0;
	struct drm_connector_state *state;

	if ((I915_READ(TV_CTL) & TV_FUSE_STATE_MASK) == TV_FUSE_STATE_DISABLED)
		return;

	if (!intel_bios_is_tv_present(dev_priv)) {
		DRM_DEBUG_KMS("Integrated TV is not present.\n");
		return;
	}

	/*
	 * Sanity check the TV output by checking to see if the
	 * DAC register holds a value
	 */
	save_tv_dac = I915_READ(TV_DAC);

	I915_WRITE(TV_DAC, save_tv_dac | TVDAC_STATE_CHG_EN);
	tv_dac_on = I915_READ(TV_DAC);

	I915_WRITE(TV_DAC, save_tv_dac & ~TVDAC_STATE_CHG_EN);
	tv_dac_off = I915_READ(TV_DAC);

	I915_WRITE(TV_DAC, save_tv_dac);

	/*
	 * If the register does not hold the state change enable
	 * bit, (either as a 0 or a 1), assume it doesn't really
	 * exist
	 */
	if ((tv_dac_on & TVDAC_STATE_CHG_EN) == 0 ||
	    (tv_dac_off & TVDAC_STATE_CHG_EN) != 0)
		return;

	intel_tv = kzalloc(sizeof(*intel_tv), GFP_KERNEL);
	if (!intel_tv) {
		return;
	}

	intel_connector = intel_connector_alloc();
	if (!intel_connector) {
		kfree(intel_tv);
		return;
	}

	intel_encoder = &intel_tv->base;
	connector = &intel_connector->base;
	state = connector->state;

	/*
	 * The documentation, for the older chipsets at least, recommend
	 * using a polling method rather than hotplug detection for TVs.
	 * This is because in order to perform the hotplug detection, the PLLs
	 * for the TV must be kept alive increasing power drain and starving
	 * bandwidth from other encoders. Notably for instance, it causes
	 * pipe underruns on Crestline when this encoder is supposedly idle.
	 *
	 * More recent chipsets favour HDMI rather than integrated S-Video.
	 */
	intel_connector->polled = DRM_CONNECTOR_POLL_CONNECT;

	drm_connector_init(dev, connector, &intel_tv_connector_funcs,
			   DRM_MODE_CONNECTOR_SVIDEO);

	drm_encoder_init(dev, &intel_encoder->base, &intel_tv_enc_funcs,
			 DRM_MODE_ENCODER_TVDAC, "TV");

	intel_encoder->compute_config = intel_tv_compute_config;
	intel_encoder->get_config = intel_tv_get_config;
	intel_encoder->pre_enable = intel_tv_pre_enable;
	intel_encoder->enable = intel_enable_tv;
	intel_encoder->disable = intel_disable_tv;
	intel_encoder->get_hw_state = intel_tv_get_hw_state;
	intel_connector->get_hw_state = intel_connector_get_hw_state;

	intel_connector_attach_encoder(intel_connector, intel_encoder);

	intel_encoder->type = INTEL_OUTPUT_TVOUT;
	intel_encoder->power_domain = POWER_DOMAIN_PORT_OTHER;
	intel_encoder->port = PORT_NONE;
	intel_encoder->crtc_mask = (1 << 0) | (1 << 1);
	intel_encoder->cloneable = 0;
	intel_encoder->base.possible_crtcs = ((1 << 0) | (1 << 1));
	intel_tv->type = DRM_MODE_CONNECTOR_Unknown;

	/* BIOS margin values */
	state->tv.margins.left = 54;
	state->tv.margins.top = 36;
	state->tv.margins.right = 46;
	state->tv.margins.bottom = 37;

	state->tv.mode = initial_mode;

	drm_connector_helper_add(connector, &intel_tv_connector_helper_funcs);
	connector->interlace_allowed = false;
	connector->doublescan_allowed = false;

	/* Create TV properties then attach current values */
	for (i = 0; i < ARRAY_SIZE(tv_modes); i++) {
		/* 1080p50/1080p60 not supported on gen3 */
		if (IS_GEN(dev_priv, 3) &&
		    tv_modes[i].oversample == 1)
			break;

		tv_format_names[i] = tv_modes[i].name;
	}
	drm_mode_create_tv_properties(dev, i, tv_format_names);

	drm_object_attach_property(&connector->base, dev->mode_config.tv_mode_property,
				   state->tv.mode);
	drm_object_attach_property(&connector->base,
				   dev->mode_config.tv_left_margin_property,
				   state->tv.margins.left);
	drm_object_attach_property(&connector->base,
				   dev->mode_config.tv_top_margin_property,
				   state->tv.margins.top);
	drm_object_attach_property(&connector->base,
				   dev->mode_config.tv_right_margin_property,
				   state->tv.margins.right);
	drm_object_attach_property(&connector->base,
				   dev->mode_config.tv_bottom_margin_property,
				   state->tv.margins.bottom);
}