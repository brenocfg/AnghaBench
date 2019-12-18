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
typedef  size_t u32 ;
struct seq_file {int dummy; } ;
struct TYPE_2__ {scalar_t__ psr2_enabled; } ;
struct drm_i915_private {TYPE_1__ psr; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (char const* const*) ; 
 int /*<<< orphan*/  EDP_PSR2_STATUS ; 
 size_t EDP_PSR2_STATUS_STATE_MASK ; 
 size_t EDP_PSR2_STATUS_STATE_SHIFT ; 
 int /*<<< orphan*/  EDP_PSR_STATUS ; 
 size_t EDP_PSR_STATUS_STATE_MASK ; 
 size_t EDP_PSR_STATUS_STATE_SHIFT ; 
 size_t I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,char const*,size_t) ; 

__attribute__((used)) static void
psr_source_status(struct drm_i915_private *dev_priv, struct seq_file *m)
{
	u32 val, status_val;
	const char *status = "unknown";

	if (dev_priv->psr.psr2_enabled) {
		static const char * const live_status[] = {
			"IDLE",
			"CAPTURE",
			"CAPTURE_FS",
			"SLEEP",
			"BUFON_FW",
			"ML_UP",
			"SU_STANDBY",
			"FAST_SLEEP",
			"DEEP_SLEEP",
			"BUF_ON",
			"TG_ON"
		};
		val = I915_READ(EDP_PSR2_STATUS);
		status_val = (val & EDP_PSR2_STATUS_STATE_MASK) >>
			      EDP_PSR2_STATUS_STATE_SHIFT;
		if (status_val < ARRAY_SIZE(live_status))
			status = live_status[status_val];
	} else {
		static const char * const live_status[] = {
			"IDLE",
			"SRDONACK",
			"SRDENT",
			"BUFOFF",
			"BUFON",
			"AUXACK",
			"SRDOFFACK",
			"SRDENT_ON",
		};
		val = I915_READ(EDP_PSR_STATUS);
		status_val = (val & EDP_PSR_STATUS_STATE_MASK) >>
			      EDP_PSR_STATUS_STATE_SHIFT;
		if (status_val < ARRAY_SIZE(live_status))
			status = live_status[status_val];
	}

	seq_printf(m, "Source PSR status: %s [0x%08x]\n", status, val);
}