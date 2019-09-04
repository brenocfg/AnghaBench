#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct intel_dp {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  dev; } ;
struct TYPE_7__ {TYPE_4__ base; } ;
struct intel_digital_port {TYPE_3__ base; int /*<<< orphan*/  (* write_infoframe ) (TYPE_4__*,struct intel_crtc_state const*,int /*<<< orphan*/ ,struct edp_vsc_psr*,int) ;} ;
struct intel_crtc_state {int dummy; } ;
struct TYPE_6__ {int HB1; int HB2; int HB3; scalar_t__ HB0; } ;
struct edp_vsc_psr {TYPE_2__ sdp_header; } ;
struct TYPE_5__ {scalar_t__ colorimetry_support; scalar_t__ psr2_enabled; } ;
struct drm_i915_private {TYPE_1__ psr; } ;
typedef  int /*<<< orphan*/  psr_vsc ;

/* Variables and functions */
 int /*<<< orphan*/  DP_SDP_VSC ; 
 struct intel_digital_port* dp_to_dig_port (struct intel_dp*) ; 
 int /*<<< orphan*/  memset (struct edp_vsc_psr*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*,struct intel_crtc_state const*,int /*<<< orphan*/ ,struct edp_vsc_psr*,int) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void intel_psr_setup_vsc(struct intel_dp *intel_dp,
				const struct intel_crtc_state *crtc_state)
{
	struct intel_digital_port *intel_dig_port = dp_to_dig_port(intel_dp);
	struct drm_i915_private *dev_priv = to_i915(intel_dig_port->base.base.dev);
	struct edp_vsc_psr psr_vsc;

	if (dev_priv->psr.psr2_enabled) {
		/* Prepare VSC Header for SU as per EDP 1.4 spec, Table 6.11 */
		memset(&psr_vsc, 0, sizeof(psr_vsc));
		psr_vsc.sdp_header.HB0 = 0;
		psr_vsc.sdp_header.HB1 = 0x7;
		if (dev_priv->psr.colorimetry_support) {
			psr_vsc.sdp_header.HB2 = 0x5;
			psr_vsc.sdp_header.HB3 = 0x13;
		} else {
			psr_vsc.sdp_header.HB2 = 0x4;
			psr_vsc.sdp_header.HB3 = 0xe;
		}
	} else {
		/* Prepare VSC packet as per EDP 1.3 spec, Table 3.10 */
		memset(&psr_vsc, 0, sizeof(psr_vsc));
		psr_vsc.sdp_header.HB0 = 0;
		psr_vsc.sdp_header.HB1 = 0x7;
		psr_vsc.sdp_header.HB2 = 0x2;
		psr_vsc.sdp_header.HB3 = 0x8;
	}

	intel_dig_port->write_infoframe(&intel_dig_port->base.base, crtc_state,
					DP_SDP_VSC, &psr_vsc, sizeof(psr_vsc));
}