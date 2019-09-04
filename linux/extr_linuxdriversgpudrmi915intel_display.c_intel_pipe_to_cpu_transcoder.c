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
struct intel_crtc {TYPE_1__* config; } ;
struct drm_i915_private {int dummy; } ;
typedef  enum transcoder { ____Placeholder_transcoder } transcoder ;
typedef  enum pipe { ____Placeholder_pipe } pipe ;
struct TYPE_2__ {int cpu_transcoder; } ;

/* Variables and functions */
 struct intel_crtc* intel_get_crtc_for_pipe (struct drm_i915_private*,int) ; 

enum transcoder intel_pipe_to_cpu_transcoder(struct drm_i915_private *dev_priv,
					     enum pipe pipe)
{
	struct intel_crtc *crtc = intel_get_crtc_for_pipe(dev_priv, pipe);

	return crtc->config->cpu_transcoder;
}