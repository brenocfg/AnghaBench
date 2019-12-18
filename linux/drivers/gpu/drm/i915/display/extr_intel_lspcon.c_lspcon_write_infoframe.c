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
struct intel_lspcon {scalar_t__ vendor; } ;
struct intel_encoder {int /*<<< orphan*/  base; } ;
struct intel_dp {int /*<<< orphan*/  aux; } ;
struct intel_crtc_state {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*) ; 
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 unsigned int HDMI_INFOFRAME_TYPE_AVI ; 
 scalar_t__ LSPCON_VENDOR_MCA ; 
 int _lspcon_write_avi_infoframe_mca (int /*<<< orphan*/ *,void const*,int /*<<< orphan*/ ) ; 
 int _lspcon_write_avi_infoframe_parade (int /*<<< orphan*/ *,void const*,int /*<<< orphan*/ ) ; 
 struct intel_dp* enc_to_intel_dp (int /*<<< orphan*/ *) ; 
 struct intel_lspcon* enc_to_intel_lspcon (int /*<<< orphan*/ *) ; 

void lspcon_write_infoframe(struct intel_encoder *encoder,
			    const struct intel_crtc_state *crtc_state,
			    unsigned int type,
			    const void *frame, ssize_t len)
{
	bool ret;
	struct intel_dp *intel_dp = enc_to_intel_dp(&encoder->base);
	struct intel_lspcon *lspcon = enc_to_intel_lspcon(&encoder->base);

	/* LSPCON only needs AVI IF */
	if (type != HDMI_INFOFRAME_TYPE_AVI)
		return;

	if (lspcon->vendor == LSPCON_VENDOR_MCA)
		ret = _lspcon_write_avi_infoframe_mca(&intel_dp->aux,
						      frame, len);
	else
		ret = _lspcon_write_avi_infoframe_parade(&intel_dp->aux,
							 frame, len);

	if (!ret) {
		DRM_ERROR("Failed to write AVI infoframes\n");
		return;
	}

	DRM_DEBUG_DRIVER("AVI infoframes updated successfully\n");
}