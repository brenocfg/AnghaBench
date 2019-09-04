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
typedef  scalar_t__ uint32_t ;
struct radeon_hdmi_acr {int /*<<< orphan*/  n_48khz; int /*<<< orphan*/  cts_48khz; int /*<<< orphan*/  n_44_1khz; int /*<<< orphan*/  cts_44_1khz; int /*<<< orphan*/  n_32khz; int /*<<< orphan*/  cts_32khz; } ;
struct radeon_device {int dummy; } ;
struct drm_encoder {struct drm_device* dev; } ;
struct drm_device {struct radeon_device* dev_private; } ;

/* Variables and functions */
 scalar_t__ ASIC_IS_DCE3 (struct radeon_device*) ; 
 scalar_t__ DCE3_HDMI0_ACR_PACKET_CONTROL ; 
 scalar_t__ HDMI0_ACR_32_0 ; 
 scalar_t__ HDMI0_ACR_32_1 ; 
 scalar_t__ HDMI0_ACR_44_0 ; 
 scalar_t__ HDMI0_ACR_44_1 ; 
 scalar_t__ HDMI0_ACR_48_0 ; 
 scalar_t__ HDMI0_ACR_48_1 ; 
 int HDMI0_ACR_AUTO_SEND ; 
 int HDMI0_ACR_CTS_32 (int /*<<< orphan*/ ) ; 
 int HDMI0_ACR_CTS_32_MASK ; 
 int HDMI0_ACR_CTS_44 (int /*<<< orphan*/ ) ; 
 int HDMI0_ACR_CTS_44_MASK ; 
 int HDMI0_ACR_CTS_48 (int /*<<< orphan*/ ) ; 
 int HDMI0_ACR_CTS_48_MASK ; 
 int HDMI0_ACR_N_32 (int /*<<< orphan*/ ) ; 
 int HDMI0_ACR_N_32_MASK ; 
 int HDMI0_ACR_N_44 (int /*<<< orphan*/ ) ; 
 int HDMI0_ACR_N_44_MASK ; 
 int HDMI0_ACR_N_48 (int /*<<< orphan*/ ) ; 
 int HDMI0_ACR_N_48_MASK ; 
 scalar_t__ HDMI0_ACR_PACKET_CONTROL ; 
 int HDMI0_ACR_SOURCE ; 
 int /*<<< orphan*/  WREG32_P (scalar_t__,int,int) ; 

void r600_hdmi_update_acr(struct drm_encoder *encoder, long offset,
	const struct radeon_hdmi_acr *acr)
{
	struct drm_device *dev = encoder->dev;
	struct radeon_device *rdev = dev->dev_private;

	/* DCE 3.0 uses register that's normally for CRC_CONTROL */
	uint32_t acr_ctl = ASIC_IS_DCE3(rdev) ? DCE3_HDMI0_ACR_PACKET_CONTROL :
				       HDMI0_ACR_PACKET_CONTROL;
	WREG32_P(acr_ctl + offset,
		HDMI0_ACR_SOURCE |		/* select SW CTS value */
		HDMI0_ACR_AUTO_SEND,	/* allow hw to sent ACR packets when required */
		~(HDMI0_ACR_SOURCE |
		HDMI0_ACR_AUTO_SEND));

	WREG32_P(HDMI0_ACR_32_0 + offset,
		HDMI0_ACR_CTS_32(acr->cts_32khz),
		~HDMI0_ACR_CTS_32_MASK);
	WREG32_P(HDMI0_ACR_32_1 + offset,
		HDMI0_ACR_N_32(acr->n_32khz),
		~HDMI0_ACR_N_32_MASK);

	WREG32_P(HDMI0_ACR_44_0 + offset,
		HDMI0_ACR_CTS_44(acr->cts_44_1khz),
		~HDMI0_ACR_CTS_44_MASK);
	WREG32_P(HDMI0_ACR_44_1 + offset,
		HDMI0_ACR_N_44(acr->n_44_1khz),
		~HDMI0_ACR_N_44_MASK);

	WREG32_P(HDMI0_ACR_48_0 + offset,
		HDMI0_ACR_CTS_48(acr->cts_48khz),
		~HDMI0_ACR_CTS_48_MASK);
	WREG32_P(HDMI0_ACR_48_1 + offset,
		HDMI0_ACR_N_48(acr->n_48khz),
		~HDMI0_ACR_N_48_MASK);
}