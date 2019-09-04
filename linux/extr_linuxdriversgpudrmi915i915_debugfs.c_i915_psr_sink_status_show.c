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
typedef  size_t u8 ;
struct seq_file {struct drm_connector* private; } ;
struct intel_dp {int /*<<< orphan*/  aux; } ;
struct drm_i915_private {int dummy; } ;
struct drm_connector {scalar_t__ status; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  base; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (char const* const*) ; 
 int /*<<< orphan*/  CAN_PSR (struct drm_i915_private*) ; 
 size_t DP_PSR_SINK_STATE_MASK ; 
 int /*<<< orphan*/  DP_PSR_STATUS ; 
 int ENODEV ; 
 scalar_t__ connector_status_connected ; 
 int drm_dp_dpcd_readb (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t*) ; 
 struct intel_dp* enc_to_intel_dp (int /*<<< orphan*/ *) ; 
 TYPE_1__* intel_attached_encoder (struct drm_connector*) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,size_t,char const*) ; 
 int /*<<< orphan*/  seq_puts (struct seq_file*,char*) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int i915_psr_sink_status_show(struct seq_file *m, void *data)
{
	u8 val;
	static const char * const sink_status[] = {
		"inactive",
		"transition to active, capture and display",
		"active, display from RFB",
		"active, capture and display on sink device timings",
		"transition to inactive, capture and display, timing re-sync",
		"reserved",
		"reserved",
		"sink internal error",
	};
	struct drm_connector *connector = m->private;
	struct drm_i915_private *dev_priv = to_i915(connector->dev);
	struct intel_dp *intel_dp =
		enc_to_intel_dp(&intel_attached_encoder(connector)->base);
	int ret;

	if (!CAN_PSR(dev_priv)) {
		seq_puts(m, "PSR Unsupported\n");
		return -ENODEV;
	}

	if (connector->status != connector_status_connected)
		return -ENODEV;

	ret = drm_dp_dpcd_readb(&intel_dp->aux, DP_PSR_STATUS, &val);

	if (ret == 1) {
		const char *str = "unknown";

		val &= DP_PSR_SINK_STATE_MASK;
		if (val < ARRAY_SIZE(sink_status))
			str = sink_status[val];
		seq_printf(m, "Sink PSR status: 0x%x [%s]\n", val, str);
	} else {
		return ret;
	}

	return 0;
}