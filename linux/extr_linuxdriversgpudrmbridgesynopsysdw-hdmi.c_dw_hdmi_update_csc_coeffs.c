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
typedef  int u32 ;
typedef  int u16 ;
struct TYPE_2__ {scalar_t__ enc_out_encoding; int /*<<< orphan*/  enc_in_bus_format; int /*<<< orphan*/  enc_out_bus_format; } ;
struct dw_hdmi {TYPE_1__ hdmi_data; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (int*) ; 
 scalar_t__ HDMI_CSC_COEF_A1_LSB ; 
 scalar_t__ HDMI_CSC_COEF_A1_MSB ; 
 scalar_t__ HDMI_CSC_COEF_B1_LSB ; 
 scalar_t__ HDMI_CSC_COEF_B1_MSB ; 
 scalar_t__ HDMI_CSC_COEF_C1_LSB ; 
 scalar_t__ HDMI_CSC_COEF_C1_MSB ; 
 int /*<<< orphan*/  HDMI_CSC_SCALE ; 
 int /*<<< orphan*/  HDMI_CSC_SCALE_CSCSCALE_MASK ; 
 scalar_t__ V4L2_YCBCR_ENC_601 ; 
 int** csc_coeff_default ; 
 int** csc_coeff_rgb_in_eitu601 ; 
 int** csc_coeff_rgb_in_eitu709 ; 
 int** csc_coeff_rgb_out_eitu601 ; 
 int** csc_coeff_rgb_out_eitu709 ; 
 scalar_t__ hdmi_bus_fmt_is_rgb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hdmi_modb (struct dw_hdmi*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hdmi_writeb (struct dw_hdmi*,int,scalar_t__) ; 
 scalar_t__ is_color_space_conversion (struct dw_hdmi*) ; 

__attribute__((used)) static void dw_hdmi_update_csc_coeffs(struct dw_hdmi *hdmi)
{
	const u16 (*csc_coeff)[3][4] = &csc_coeff_default;
	unsigned i;
	u32 csc_scale = 1;

	if (is_color_space_conversion(hdmi)) {
		if (hdmi_bus_fmt_is_rgb(hdmi->hdmi_data.enc_out_bus_format)) {
			if (hdmi->hdmi_data.enc_out_encoding ==
						V4L2_YCBCR_ENC_601)
				csc_coeff = &csc_coeff_rgb_out_eitu601;
			else
				csc_coeff = &csc_coeff_rgb_out_eitu709;
		} else if (hdmi_bus_fmt_is_rgb(
					hdmi->hdmi_data.enc_in_bus_format)) {
			if (hdmi->hdmi_data.enc_out_encoding ==
						V4L2_YCBCR_ENC_601)
				csc_coeff = &csc_coeff_rgb_in_eitu601;
			else
				csc_coeff = &csc_coeff_rgb_in_eitu709;
			csc_scale = 0;
		}
	}

	/* The CSC registers are sequential, alternating MSB then LSB */
	for (i = 0; i < ARRAY_SIZE(csc_coeff_default[0]); i++) {
		u16 coeff_a = (*csc_coeff)[0][i];
		u16 coeff_b = (*csc_coeff)[1][i];
		u16 coeff_c = (*csc_coeff)[2][i];

		hdmi_writeb(hdmi, coeff_a & 0xff, HDMI_CSC_COEF_A1_LSB + i * 2);
		hdmi_writeb(hdmi, coeff_a >> 8, HDMI_CSC_COEF_A1_MSB + i * 2);
		hdmi_writeb(hdmi, coeff_b & 0xff, HDMI_CSC_COEF_B1_LSB + i * 2);
		hdmi_writeb(hdmi, coeff_b >> 8, HDMI_CSC_COEF_B1_MSB + i * 2);
		hdmi_writeb(hdmi, coeff_c & 0xff, HDMI_CSC_COEF_C1_LSB + i * 2);
		hdmi_writeb(hdmi, coeff_c >> 8, HDMI_CSC_COEF_C1_MSB + i * 2);
	}

	hdmi_modb(hdmi, csc_scale, HDMI_CSC_SCALE_CSCSCALE_MASK,
		  HDMI_CSC_SCALE);
}