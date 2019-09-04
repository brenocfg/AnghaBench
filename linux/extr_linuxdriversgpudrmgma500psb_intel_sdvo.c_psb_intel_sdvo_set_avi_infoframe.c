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
struct psb_intel_sdvo {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_INFO (char*) ; 

__attribute__((used)) static bool psb_intel_sdvo_set_avi_infoframe(struct psb_intel_sdvo *psb_intel_sdvo)
{
	DRM_INFO("HDMI is not supported yet");

	return false;
#if 0
	struct dip_infoframe avi_if = {
		.type = DIP_TYPE_AVI,
		.ver = DIP_VERSION_AVI,
		.len = DIP_LEN_AVI,
	};
	uint8_t tx_rate = SDVO_HBUF_TX_VSYNC;
	uint8_t set_buf_index[2] = { 1, 0 };
	uint64_t *data = (uint64_t *)&avi_if;
	unsigned i;

	intel_dip_infoframe_csum(&avi_if);

	if (!psb_intel_sdvo_set_value(psb_intel_sdvo,
				  SDVO_CMD_SET_HBUF_INDEX,
				  set_buf_index, 2))
		return false;

	for (i = 0; i < sizeof(avi_if); i += 8) {
		if (!psb_intel_sdvo_set_value(psb_intel_sdvo,
					  SDVO_CMD_SET_HBUF_DATA,
					  data, 8))
			return false;
		data++;
	}

	return psb_intel_sdvo_set_value(psb_intel_sdvo,
				    SDVO_CMD_SET_HBUF_TXRATE,
				    &tx_rate, 1);
#endif
}