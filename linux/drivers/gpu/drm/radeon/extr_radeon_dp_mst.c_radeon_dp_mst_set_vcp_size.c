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
typedef  int uint32_t ;
struct radeon_encoder_mst {int /*<<< orphan*/  fe; } ;
struct TYPE_2__ {struct drm_device* dev; } ;
struct radeon_encoder {struct radeon_encoder_mst* enc_priv; TYPE_1__ base; } ;
struct radeon_device {int dummy; } ;
struct drm_device {struct radeon_device* dev_private; } ;
typedef  int s64 ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,int /*<<< orphan*/ ) ; 
 int NI_DP_MSE_RATE_CNTL ; 
 int NI_DP_MSE_RATE_UPDATE ; 
 int NI_DP_MSE_RATE_X (int) ; 
 int NI_DP_MSE_RATE_Y (int) ; 
 int RREG32 (int) ; 
 int /*<<< orphan*/  WREG32 (int,int) ; 
 int drm_fixp2int (int) ; 
 int drm_fixp2int_ceil (int) ; 
 int radeon_atom_set_enc_offset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int radeon_dp_mst_set_vcp_size(struct radeon_encoder *mst, s64 avg_time_slots_per_mtp)
{
	struct drm_device *dev = mst->base.dev;
	struct radeon_device *rdev = dev->dev_private;
	struct radeon_encoder_mst *mst_enc = mst->enc_priv;
	uint32_t val, temp;
	uint32_t offset = radeon_atom_set_enc_offset(mst_enc->fe);
	int retries = 0;
	uint32_t x = drm_fixp2int(avg_time_slots_per_mtp);
	uint32_t y = drm_fixp2int_ceil((avg_time_slots_per_mtp - x) << 26);

	val = NI_DP_MSE_RATE_X(x) | NI_DP_MSE_RATE_Y(y);

	WREG32(NI_DP_MSE_RATE_CNTL + offset, val);

	do {
		temp = RREG32(NI_DP_MSE_RATE_UPDATE + offset);
		udelay(10);
	} while ((temp & 0x1) && (retries++ < 10000));

	if (retries >= 10000)
		DRM_ERROR("timed out wait for rate cntl %d\n", mst_enc->fe);
	return 0;
}