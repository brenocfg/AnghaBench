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
typedef  int /*<<< orphan*/  u32 ;
struct radeon_encoder_atom_dig {TYPE_2__* afmt; } ;
struct radeon_encoder {int encoder_id; struct radeon_encoder_atom_dig* enc_priv; } ;
struct TYPE_3__ {scalar_t__ installed; } ;
struct radeon_device {TYPE_1__ irq; int /*<<< orphan*/  dev; } ;
struct drm_encoder {struct drm_device* dev; } ;
struct drm_device {struct radeon_device* dev_private; } ;
struct TYPE_4__ {int enabled; scalar_t__ offset; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASIC_IS_DCE3 (struct radeon_device*) ; 
 int /*<<< orphan*/  AVIVO_LVTMA_CNTL ; 
 int /*<<< orphan*/  AVIVO_LVTMA_CNTL_HDMI_EN ; 
 int /*<<< orphan*/  AVIVO_TMDSA_CNTL ; 
 int /*<<< orphan*/  AVIVO_TMDSA_CNTL_HDMI_EN ; 
 int /*<<< orphan*/  DDIA_CNTL ; 
 int /*<<< orphan*/  DDIA_HDMI_EN ; 
 int /*<<< orphan*/  DRM_DEBUG (char*,char*,scalar_t__,int) ; 
#define  ENCODER_OBJECT_ID_INTERNAL_DDI 131 
#define  ENCODER_OBJECT_ID_INTERNAL_KLDSCP_DVO1 130 
#define  ENCODER_OBJECT_ID_INTERNAL_KLDSCP_TMDS1 129 
#define  ENCODER_OBJECT_ID_INTERNAL_LVTM1 128 
 scalar_t__ HDMI0_CONTROL ; 
 int /*<<< orphan*/  HDMI0_ENABLE ; 
 int /*<<< orphan*/  HDMI0_ERROR_ACK ; 
 int /*<<< orphan*/  HDMI0_STREAM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HDMI0_STREAM_DDIA ; 
 int /*<<< orphan*/  HDMI0_STREAM_DVOA ; 
 int /*<<< orphan*/  HDMI0_STREAM_LVTMA ; 
 int /*<<< orphan*/  HDMI0_STREAM_TMDSA ; 
 int /*<<< orphan*/  WREG32 (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32_AND (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32_OR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  radeon_irq_kms_disable_afmt (struct radeon_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  radeon_irq_kms_enable_afmt (struct radeon_device*,int /*<<< orphan*/ ) ; 
 struct radeon_encoder* to_radeon_encoder (struct drm_encoder*) ; 

void r600_hdmi_enable(struct drm_encoder *encoder, bool enable)
{
	struct drm_device *dev = encoder->dev;
	struct radeon_device *rdev = dev->dev_private;
	struct radeon_encoder *radeon_encoder = to_radeon_encoder(encoder);
	struct radeon_encoder_atom_dig *dig = radeon_encoder->enc_priv;
	u32 hdmi = HDMI0_ERROR_ACK;

	if (!dig || !dig->afmt)
		return;

	/* Older chipsets require setting HDMI and routing manually */
	if (!ASIC_IS_DCE3(rdev)) {
		if (enable)
			hdmi |= HDMI0_ENABLE;
		switch (radeon_encoder->encoder_id) {
		case ENCODER_OBJECT_ID_INTERNAL_KLDSCP_TMDS1:
			if (enable) {
				WREG32_OR(AVIVO_TMDSA_CNTL, AVIVO_TMDSA_CNTL_HDMI_EN);
				hdmi |= HDMI0_STREAM(HDMI0_STREAM_TMDSA);
			} else {
				WREG32_AND(AVIVO_TMDSA_CNTL, ~AVIVO_TMDSA_CNTL_HDMI_EN);
			}
			break;
		case ENCODER_OBJECT_ID_INTERNAL_LVTM1:
			if (enable) {
				WREG32_OR(AVIVO_LVTMA_CNTL, AVIVO_LVTMA_CNTL_HDMI_EN);
				hdmi |= HDMI0_STREAM(HDMI0_STREAM_LVTMA);
			} else {
				WREG32_AND(AVIVO_LVTMA_CNTL, ~AVIVO_LVTMA_CNTL_HDMI_EN);
			}
			break;
		case ENCODER_OBJECT_ID_INTERNAL_DDI:
			if (enable) {
				WREG32_OR(DDIA_CNTL, DDIA_HDMI_EN);
				hdmi |= HDMI0_STREAM(HDMI0_STREAM_DDIA);
			} else {
				WREG32_AND(DDIA_CNTL, ~DDIA_HDMI_EN);
			}
			break;
		case ENCODER_OBJECT_ID_INTERNAL_KLDSCP_DVO1:
			if (enable)
				hdmi |= HDMI0_STREAM(HDMI0_STREAM_DVOA);
			break;
		default:
			dev_err(rdev->dev, "Invalid encoder for HDMI: 0x%X\n",
				radeon_encoder->encoder_id);
			break;
		}
		WREG32(HDMI0_CONTROL + dig->afmt->offset, hdmi);
	}

	if (rdev->irq.installed) {
		/* if irq is available use it */
		/* XXX: shouldn't need this on any asics.  Double check DCE2/3 */
		if (enable)
			radeon_irq_kms_enable_afmt(rdev, dig->afmt->id);
		else
			radeon_irq_kms_disable_afmt(rdev, dig->afmt->id);
	}

	dig->afmt->enabled = enable;

	DRM_DEBUG("%sabling HDMI interface @ 0x%04X for encoder 0x%x\n",
		  enable ? "En" : "Dis", dig->afmt->offset, radeon_encoder->encoder_id);
}