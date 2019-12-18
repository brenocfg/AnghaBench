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
typedef  int /*<<< orphan*/  vsc_sdp ;
struct intel_dp {int dummy; } ;
struct intel_digital_port {int /*<<< orphan*/  base; int /*<<< orphan*/  (* write_infoframe ) (int /*<<< orphan*/ *,struct intel_crtc_state const*,int /*<<< orphan*/ ,struct dp_sdp*,int) ;} ;
struct intel_crtc_state {int pipe_bpp; } ;
struct TYPE_2__ {int HB1; int HB2; int HB3; scalar_t__ HB0; } ;
struct dp_sdp {int* db; TYPE_1__ sdp_header; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_SDP_VSC ; 
 int /*<<< orphan*/  MISSING_CASE (int) ; 
 struct intel_digital_port* dp_to_dig_port (struct intel_dp*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,struct intel_crtc_state const*,int /*<<< orphan*/ ,struct dp_sdp*,int) ; 

__attribute__((used)) static void
intel_pixel_encoding_setup_vsc(struct intel_dp *intel_dp,
			       const struct intel_crtc_state *crtc_state)
{
	struct intel_digital_port *intel_dig_port = dp_to_dig_port(intel_dp);
	struct dp_sdp vsc_sdp = {};

	/* Prepare VSC Header for SU as per DP 1.4a spec, Table 2-119 */
	vsc_sdp.sdp_header.HB0 = 0;
	vsc_sdp.sdp_header.HB1 = 0x7;

	/*
	 * VSC SDP supporting 3D stereo, PSR2, and Pixel Encoding/
	 * Colorimetry Format indication.
	 */
	vsc_sdp.sdp_header.HB2 = 0x5;

	/*
	 * VSC SDP supporting 3D stereo, + PSR2, + Pixel Encoding/
	 * Colorimetry Format indication (HB2 = 05h).
	 */
	vsc_sdp.sdp_header.HB3 = 0x13;

	/*
	 * YCbCr 420 = 3h DB16[7:4] ITU-R BT.601 = 0h, ITU-R BT.709 = 1h
	 * DB16[3:0] DP 1.4a spec, Table 2-120
	 */
	vsc_sdp.db[16] = 0x3 << 4; /* 0x3 << 4 , YCbCr 420*/
	/* RGB->YCBCR color conversion uses the BT.709 color space. */
	vsc_sdp.db[16] |= 0x1; /* 0x1, ITU-R BT.709 */

	/*
	 * For pixel encoding formats YCbCr444, YCbCr422, YCbCr420, and Y Only,
	 * the following Component Bit Depth values are defined:
	 * 001b = 8bpc.
	 * 010b = 10bpc.
	 * 011b = 12bpc.
	 * 100b = 16bpc.
	 */
	switch (crtc_state->pipe_bpp) {
	case 24: /* 8bpc */
		vsc_sdp.db[17] = 0x1;
		break;
	case 30: /* 10bpc */
		vsc_sdp.db[17] = 0x2;
		break;
	case 36: /* 12bpc */
		vsc_sdp.db[17] = 0x3;
		break;
	case 48: /* 16bpc */
		vsc_sdp.db[17] = 0x4;
		break;
	default:
		MISSING_CASE(crtc_state->pipe_bpp);
		break;
	}

	/*
	 * Dynamic Range (Bit 7)
	 * 0 = VESA range, 1 = CTA range.
	 * all YCbCr are always limited range
	 */
	vsc_sdp.db[17] |= 0x80;

	/*
	 * Content Type (Bits 2:0)
	 * 000b = Not defined.
	 * 001b = Graphics.
	 * 010b = Photo.
	 * 011b = Video.
	 * 100b = Game
	 * All other values are RESERVED.
	 * Note: See CTA-861-G for the definition and expected
	 * processing by a stream sink for the above contect types.
	 */
	vsc_sdp.db[18] = 0;

	intel_dig_port->write_infoframe(&intel_dig_port->base,
			crtc_state, DP_SDP_VSC, &vsc_sdp, sizeof(vsc_sdp));
}