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
typedef  int /*<<< orphan*/  u32 ;
struct intel_engine_cs {int id; int /*<<< orphan*/  mmio_base; struct drm_i915_private* i915; } ;
struct drm_i915_private {int dummy; } ;
typedef  int /*<<< orphan*/  i915_reg_t ;

/* Variables and functions */
#define  BCS0 131 
 int /*<<< orphan*/  BLT_HWS_PGA_GEN7 ; 
 int /*<<< orphan*/  BSD_HWS_PGA_GEN7 ; 
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ IS_GEN (struct drm_i915_private*,int) ; 
 int /*<<< orphan*/  POSTING_READ (int /*<<< orphan*/ ) ; 
#define  RCS0 130 
 int /*<<< orphan*/  RENDER_HWS_PGA_GEN7 ; 
 int /*<<< orphan*/  RING_HWS_PGA (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RING_HWS_PGA_GEN6 (int /*<<< orphan*/ ) ; 
#define  VCS0 129 
 int /*<<< orphan*/  VEBOX_HWS_PGA_GEN7 ; 
#define  VECS0 128 

__attribute__((used)) static void set_hwsp(struct intel_engine_cs *engine, u32 offset)
{
	struct drm_i915_private *dev_priv = engine->i915;
	i915_reg_t hwsp;

	/*
	 * The ring status page addresses are no longer next to the rest of
	 * the ring registers as of gen7.
	 */
	if (IS_GEN(dev_priv, 7)) {
		switch (engine->id) {
		/*
		 * No more rings exist on Gen7. Default case is only to shut up
		 * gcc switch check warning.
		 */
		default:
			GEM_BUG_ON(engine->id);
			/* fallthrough */
		case RCS0:
			hwsp = RENDER_HWS_PGA_GEN7;
			break;
		case BCS0:
			hwsp = BLT_HWS_PGA_GEN7;
			break;
		case VCS0:
			hwsp = BSD_HWS_PGA_GEN7;
			break;
		case VECS0:
			hwsp = VEBOX_HWS_PGA_GEN7;
			break;
		}
	} else if (IS_GEN(dev_priv, 6)) {
		hwsp = RING_HWS_PGA_GEN6(engine->mmio_base);
	} else {
		hwsp = RING_HWS_PGA(engine->mmio_base);
	}

	I915_WRITE(hwsp, offset);
	POSTING_READ(hwsp);
}