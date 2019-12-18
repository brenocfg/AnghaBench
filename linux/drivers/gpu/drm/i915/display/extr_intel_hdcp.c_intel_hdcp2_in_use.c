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
typedef  int u32 ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;
struct intel_connector {TYPE_2__* encoder; TYPE_1__ base; } ;
struct drm_i915_private {int dummy; } ;
typedef  enum port { ____Placeholder_port } port ;
struct TYPE_4__ {int port; } ;

/* Variables and functions */
 int /*<<< orphan*/  HDCP2_STATUS_DDI (int) ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int LINK_ENCRYPTION_STATUS ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool intel_hdcp2_in_use(struct intel_connector *connector)
{
	struct drm_i915_private *dev_priv = to_i915(connector->base.dev);
	enum port port = connector->encoder->port;
	u32 reg;

	reg = I915_READ(HDCP2_STATUS_DDI(port));
	return reg & LINK_ENCRYPTION_STATUS;
}