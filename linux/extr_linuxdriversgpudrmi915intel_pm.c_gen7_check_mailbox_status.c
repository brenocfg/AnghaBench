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
typedef  int uint32_t ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENXIO ; 
 int EOVERFLOW ; 
 int ETIMEDOUT ; 
 int GEN6_PCODE_ERROR_MASK ; 
#define  GEN6_PCODE_ILLEGAL_CMD 132 
 int /*<<< orphan*/  GEN6_PCODE_MAILBOX ; 
#define  GEN6_PCODE_SUCCESS 131 
#define  GEN7_PCODE_ILLEGAL_DATA 130 
#define  GEN7_PCODE_MIN_FREQ_TABLE_GT_RATIO_OUT_OF_RANGE 129 
#define  GEN7_PCODE_TIMEOUT 128 
 int I915_READ_FW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MISSING_CASE (int) ; 

__attribute__((used)) static inline int gen7_check_mailbox_status(struct drm_i915_private *dev_priv)
{
	uint32_t flags =
		I915_READ_FW(GEN6_PCODE_MAILBOX) & GEN6_PCODE_ERROR_MASK;

	switch (flags) {
	case GEN6_PCODE_SUCCESS:
		return 0;
	case GEN6_PCODE_ILLEGAL_CMD:
		return -ENXIO;
	case GEN7_PCODE_TIMEOUT:
		return -ETIMEDOUT;
	case GEN7_PCODE_ILLEGAL_DATA:
		return -EINVAL;
	case GEN7_PCODE_MIN_FREQ_TABLE_GT_RATIO_OUT_OF_RANGE:
		return -EOVERFLOW;
	default:
		MISSING_CASE(flags);
		return 0;
	}
}