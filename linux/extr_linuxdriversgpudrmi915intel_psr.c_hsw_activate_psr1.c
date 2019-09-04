#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct intel_dp {int /*<<< orphan*/  dpcd; } ;
struct TYPE_6__ {struct drm_device* dev; } ;
struct TYPE_7__ {TYPE_1__ base; } ;
struct intel_digital_port {TYPE_2__ base; } ;
struct TYPE_9__ {int idle_frames; int tp1_wakeup_time_us; int tp2_tp3_wakeup_time_us; } ;
struct TYPE_10__ {TYPE_4__ psr; } ;
struct TYPE_8__ {int sink_sync_latency; scalar_t__ link_standby; } ;
struct drm_i915_private {TYPE_5__ vbt; TYPE_3__ psr; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int EDP_PSR_CRC_ENABLE ; 
 int /*<<< orphan*/  EDP_PSR_CTL ; 
 int EDP_PSR_ENABLE ; 
 int EDP_PSR_IDLE_FRAME_SHIFT ; 
 int EDP_PSR_LINK_STANDBY ; 
 int EDP_PSR_MAX_SLEEP_TIME_SHIFT ; 
 int EDP_PSR_MIN_LINK_ENTRY_TIME_8_LINES ; 
 int EDP_PSR_RESTORE_PSR_ACTIVE_CTX_MASK ; 
 int EDP_PSR_TP1_TIME_0us ; 
 int EDP_PSR_TP1_TIME_100us ; 
 int EDP_PSR_TP1_TIME_2500us ; 
 int EDP_PSR_TP1_TIME_500us ; 
 int EDP_PSR_TP1_TP2_SEL ; 
 int EDP_PSR_TP1_TP3_SEL ; 
 int EDP_PSR_TP2_TP3_TIME_0us ; 
 int EDP_PSR_TP2_TP3_TIME_100us ; 
 int EDP_PSR_TP2_TP3_TIME_2500us ; 
 int EDP_PSR_TP2_TP3_TIME_500us ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int) ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 scalar_t__ IS_HASWELL (struct drm_i915_private*) ; 
 struct intel_digital_port* dp_to_dig_port (struct intel_dp*) ; 
 scalar_t__ drm_dp_tps3_supported (int /*<<< orphan*/ ) ; 
 scalar_t__ intel_dp_source_supports_hbr2 (struct intel_dp*) ; 
 int max (int,int) ; 
 struct drm_i915_private* to_i915 (struct drm_device*) ; 

__attribute__((used)) static void hsw_activate_psr1(struct intel_dp *intel_dp)
{
	struct intel_digital_port *dig_port = dp_to_dig_port(intel_dp);
	struct drm_device *dev = dig_port->base.base.dev;
	struct drm_i915_private *dev_priv = to_i915(dev);
	u32 max_sleep_time = 0x1f;
	u32 val = EDP_PSR_ENABLE;

	/* Let's use 6 as the minimum to cover all known cases including the
	 * off-by-one issue that HW has in some cases.
	 */
	int idle_frames = max(6, dev_priv->vbt.psr.idle_frames);

	/* sink_sync_latency of 8 means source has to wait for more than 8
	 * frames, we'll go with 9 frames for now
	 */
	idle_frames = max(idle_frames, dev_priv->psr.sink_sync_latency + 1);
	val |= idle_frames << EDP_PSR_IDLE_FRAME_SHIFT;

	val |= max_sleep_time << EDP_PSR_MAX_SLEEP_TIME_SHIFT;
	if (IS_HASWELL(dev_priv))
		val |= EDP_PSR_MIN_LINK_ENTRY_TIME_8_LINES;

	if (dev_priv->psr.link_standby)
		val |= EDP_PSR_LINK_STANDBY;

	if (dev_priv->vbt.psr.tp1_wakeup_time_us == 0)
		val |=  EDP_PSR_TP1_TIME_0us;
	else if (dev_priv->vbt.psr.tp1_wakeup_time_us <= 100)
		val |= EDP_PSR_TP1_TIME_100us;
	else if (dev_priv->vbt.psr.tp1_wakeup_time_us <= 500)
		val |= EDP_PSR_TP1_TIME_500us;
	else
		val |= EDP_PSR_TP1_TIME_2500us;

	if (dev_priv->vbt.psr.tp2_tp3_wakeup_time_us == 0)
		val |=  EDP_PSR_TP2_TP3_TIME_0us;
	else if (dev_priv->vbt.psr.tp2_tp3_wakeup_time_us <= 100)
		val |= EDP_PSR_TP2_TP3_TIME_100us;
	else if (dev_priv->vbt.psr.tp2_tp3_wakeup_time_us <= 500)
		val |= EDP_PSR_TP2_TP3_TIME_500us;
	else
		val |= EDP_PSR_TP2_TP3_TIME_2500us;

	if (intel_dp_source_supports_hbr2(intel_dp) &&
	    drm_dp_tps3_supported(intel_dp->dpcd))
		val |= EDP_PSR_TP1_TP3_SEL;
	else
		val |= EDP_PSR_TP1_TP2_SEL;

	if (INTEL_GEN(dev_priv) >= 8)
		val |= EDP_PSR_CRC_ENABLE;

	val |= I915_READ(EDP_PSR_CTL) & EDP_PSR_RESTORE_PSR_ACTIVE_CTX_MASK;
	I915_WRITE(EDP_PSR_CTL, val);
}