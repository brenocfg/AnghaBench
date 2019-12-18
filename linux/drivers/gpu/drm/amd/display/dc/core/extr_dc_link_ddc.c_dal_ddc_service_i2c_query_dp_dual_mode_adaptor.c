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
typedef  scalar_t__ uint8_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  type2_dongle_buf ;
struct dp_hdmi_dongle_signature_data {scalar_t__ eot; scalar_t__* id; } ;
struct display_sink_capability {int dongle_type; int max_hdmi_pixel_clock; } ;
struct ddc_service {int /*<<< orphan*/  link; } ;
typedef  enum display_dongle_type { ____Placeholder_display_dongle_type } display_dongle_type ;

/* Variables and functions */
 int /*<<< orphan*/  CONN_DATA_DETECT (int /*<<< orphan*/ ,scalar_t__*,int,char*,int) ; 
 int DISPLAY_DONGLE_DP_DVI_DONGLE ; 
 int DISPLAY_DONGLE_DP_HDMI_DONGLE ; 
 int DISPLAY_DONGLE_DP_HDMI_MISMATCHED_DONGLE ; 
 int DISPLAY_DONGLE_NONE ; 
 int DP_ADAPTOR_DVI_MAX_TMDS_CLK ; 
 int DP_ADAPTOR_HDMI_SAFE_MAX_TMDS_CLK ; 
 scalar_t__ DP_ADAPTOR_TYPE2_ID ; 
 int DP_ADAPTOR_TYPE2_MAX_TMDS_CLK ; 
 int DP_ADAPTOR_TYPE2_MIN_TMDS_CLK ; 
 size_t DP_ADAPTOR_TYPE2_REG_ID ; 
 size_t DP_ADAPTOR_TYPE2_REG_MAX_TMDS_CLK ; 
 int DP_ADAPTOR_TYPE2_SIZE ; 
 int /*<<< orphan*/  DP_HDMI_DONGLE_ADDRESS ; 
 scalar_t__ DP_HDMI_DONGLE_SIGNATURE_EOT ; 
 scalar_t__* dp_hdmi_dongle_signature_str ; 
 scalar_t__ i2c_read (struct ddc_service*,int /*<<< orphan*/ ,scalar_t__*,int) ; 

void dal_ddc_service_i2c_query_dp_dual_mode_adaptor(
	struct ddc_service *ddc,
	struct display_sink_capability *sink_cap)
{
	uint8_t i;
	bool is_valid_hdmi_signature;
	enum display_dongle_type *dongle = &sink_cap->dongle_type;
	uint8_t type2_dongle_buf[DP_ADAPTOR_TYPE2_SIZE];
	bool is_type2_dongle = false;
	int retry_count = 2;
	struct dp_hdmi_dongle_signature_data *dongle_signature;

	/* Assume we have no valid DP passive dongle connected */
	*dongle = DISPLAY_DONGLE_NONE;
	sink_cap->max_hdmi_pixel_clock = DP_ADAPTOR_HDMI_SAFE_MAX_TMDS_CLK;

	/* Read DP-HDMI dongle I2c (no response interpreted as DP-DVI dongle)*/
	if (!i2c_read(
		ddc,
		DP_HDMI_DONGLE_ADDRESS,
		type2_dongle_buf,
		sizeof(type2_dongle_buf))) {
		/* Passive HDMI dongles can sometimes fail here without retrying*/
		while (retry_count > 0) {
			if (i2c_read(ddc,
				DP_HDMI_DONGLE_ADDRESS,
				type2_dongle_buf,
				sizeof(type2_dongle_buf)))
				break;
			retry_count--;
		}
		if (retry_count == 0) {
			*dongle = DISPLAY_DONGLE_DP_DVI_DONGLE;
			sink_cap->max_hdmi_pixel_clock = DP_ADAPTOR_DVI_MAX_TMDS_CLK;

			CONN_DATA_DETECT(ddc->link, type2_dongle_buf, sizeof(type2_dongle_buf),
					"DP-DVI passive dongle %dMhz: ",
					DP_ADAPTOR_DVI_MAX_TMDS_CLK / 1000);
			return;
		}
	}

	/* Check if Type 2 dongle.*/
	if (type2_dongle_buf[DP_ADAPTOR_TYPE2_REG_ID] == DP_ADAPTOR_TYPE2_ID)
		is_type2_dongle = true;

	dongle_signature =
		(struct dp_hdmi_dongle_signature_data *)type2_dongle_buf;

	is_valid_hdmi_signature = true;

	/* Check EOT */
	if (dongle_signature->eot != DP_HDMI_DONGLE_SIGNATURE_EOT) {
		is_valid_hdmi_signature = false;
	}

	/* Check signature */
	for (i = 0; i < sizeof(dongle_signature->id); ++i) {
		/* If its not the right signature,
		 * skip mismatch in subversion byte.*/
		if (dongle_signature->id[i] !=
			dp_hdmi_dongle_signature_str[i] && i != 3) {

			if (is_type2_dongle) {
				is_valid_hdmi_signature = false;
				break;
			}

		}
	}

	if (is_type2_dongle) {
		uint32_t max_tmds_clk =
			type2_dongle_buf[DP_ADAPTOR_TYPE2_REG_MAX_TMDS_CLK];

		max_tmds_clk = max_tmds_clk * 2 + max_tmds_clk / 2;

		if (0 == max_tmds_clk ||
				max_tmds_clk < DP_ADAPTOR_TYPE2_MIN_TMDS_CLK ||
				max_tmds_clk > DP_ADAPTOR_TYPE2_MAX_TMDS_CLK) {
			*dongle = DISPLAY_DONGLE_DP_DVI_DONGLE;

			CONN_DATA_DETECT(ddc->link, type2_dongle_buf,
					sizeof(type2_dongle_buf),
					"DP-DVI passive dongle %dMhz: ",
					DP_ADAPTOR_DVI_MAX_TMDS_CLK / 1000);
		} else {
			if (is_valid_hdmi_signature == true) {
				*dongle = DISPLAY_DONGLE_DP_HDMI_DONGLE;

				CONN_DATA_DETECT(ddc->link, type2_dongle_buf,
						sizeof(type2_dongle_buf),
						"Type 2 DP-HDMI passive dongle %dMhz: ",
						max_tmds_clk);
			} else {
				*dongle = DISPLAY_DONGLE_DP_HDMI_MISMATCHED_DONGLE;

				CONN_DATA_DETECT(ddc->link, type2_dongle_buf,
						sizeof(type2_dongle_buf),
						"Type 2 DP-HDMI passive dongle (no signature) %dMhz: ",
						max_tmds_clk);

			}

			/* Multiply by 1000 to convert to kHz. */
			sink_cap->max_hdmi_pixel_clock =
				max_tmds_clk * 1000;
		}

	} else {
		if (is_valid_hdmi_signature == true) {
			*dongle = DISPLAY_DONGLE_DP_HDMI_DONGLE;

			CONN_DATA_DETECT(ddc->link, type2_dongle_buf,
					sizeof(type2_dongle_buf),
					"Type 1 DP-HDMI passive dongle %dMhz: ",
					sink_cap->max_hdmi_pixel_clock / 1000);
		} else {
			*dongle = DISPLAY_DONGLE_DP_HDMI_MISMATCHED_DONGLE;

			CONN_DATA_DETECT(ddc->link, type2_dongle_buf,
					sizeof(type2_dongle_buf),
					"Type 1 DP-HDMI passive dongle (no signature) %dMhz: ",
					sink_cap->max_hdmi_pixel_clock / 1000);
		}
	}

	return;
}