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
struct dce110_stream_encoder {int dummy; } ;
struct dc_info_packet {int /*<<< orphan*/ * sb; int /*<<< orphan*/  hb3; int /*<<< orphan*/  hb2; int /*<<< orphan*/  hb1; int /*<<< orphan*/  hb0; } ;

/* Variables and functions */
 int /*<<< orphan*/  AFMT_AUDIO_CLOCK_EN ; 
 int /*<<< orphan*/  AFMT_CNTL ; 
 int /*<<< orphan*/  AFMT_GENERIC0_FRAME_UPDATE ; 
 int /*<<< orphan*/  AFMT_GENERIC0_UPDATE ; 
 int /*<<< orphan*/  AFMT_GENERIC1_FRAME_UPDATE ; 
 int /*<<< orphan*/  AFMT_GENERIC2_FRAME_UPDATE ; 
 int /*<<< orphan*/  AFMT_GENERIC2_UPDATE ; 
 int /*<<< orphan*/  AFMT_GENERIC3_FRAME_UPDATE ; 
 int /*<<< orphan*/  AFMT_GENERIC4_FRAME_UPDATE ; 
 int /*<<< orphan*/  AFMT_GENERIC5_FRAME_UPDATE ; 
 int /*<<< orphan*/  AFMT_GENERIC6_FRAME_UPDATE ; 
 int /*<<< orphan*/  AFMT_GENERIC7_FRAME_UPDATE ; 
 int /*<<< orphan*/  AFMT_GENERIC_0 ; 
 int /*<<< orphan*/  AFMT_GENERIC_1 ; 
 int /*<<< orphan*/  AFMT_GENERIC_2 ; 
 int /*<<< orphan*/  AFMT_GENERIC_3 ; 
 int /*<<< orphan*/  AFMT_GENERIC_4 ; 
 int /*<<< orphan*/  AFMT_GENERIC_5 ; 
 int /*<<< orphan*/  AFMT_GENERIC_6 ; 
 int /*<<< orphan*/  AFMT_GENERIC_7 ; 
 int /*<<< orphan*/  AFMT_GENERIC_CONFLICT ; 
 int /*<<< orphan*/  AFMT_GENERIC_CONFLICT_CLR ; 
 int /*<<< orphan*/  AFMT_GENERIC_HB0 ; 
 int /*<<< orphan*/  AFMT_GENERIC_HB1 ; 
 int /*<<< orphan*/  AFMT_GENERIC_HB2 ; 
 int /*<<< orphan*/  AFMT_GENERIC_HB3 ; 
 int /*<<< orphan*/  AFMT_GENERIC_HDR ; 
 int /*<<< orphan*/  AFMT_GENERIC_INDEX ; 
 int /*<<< orphan*/  AFMT_VBI_PACKET_CONTROL ; 
 int /*<<< orphan*/  AFMT_VBI_PACKET_CONTROL1 ; 
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 scalar_t__ REG (int /*<<< orphan*/ ) ; 
 int REG_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_SET_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_UPDATE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  REG_UPDATE_2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  REG_WAIT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  REG_WRITE (int /*<<< orphan*/ ,int const) ; 

__attribute__((used)) static void dce110_update_generic_info_packet(
	struct dce110_stream_encoder *enc110,
	uint32_t packet_index,
	const struct dc_info_packet *info_packet)
{
	uint32_t regval;
	/* TODOFPGA Figure out a proper number for max_retries polling for lock
	 * use 50 for now.
	 */
	uint32_t max_retries = 50;

	/*we need turn on clock before programming AFMT block*/
	if (REG(AFMT_CNTL))
		REG_UPDATE(AFMT_CNTL, AFMT_AUDIO_CLOCK_EN, 1);

	if (REG(AFMT_VBI_PACKET_CONTROL1)) {
		if (packet_index >= 8)
			ASSERT(0);

		/* poll dig_update_lock is not locked -> asic internal signal
		 * assume otg master lock will unlock it
		 */
/*		REG_WAIT(AFMT_VBI_PACKET_CONTROL, AFMT_GENERIC_LOCK_STATUS,
				0, 10, max_retries);*/

		/* check if HW reading GSP memory */
		REG_WAIT(AFMT_VBI_PACKET_CONTROL, AFMT_GENERIC_CONFLICT,
				0, 10, max_retries);

		/* HW does is not reading GSP memory not reading too long ->
		 * something wrong. clear GPS memory access and notify?
		 * hw SW is writing to GSP memory
		 */
		REG_UPDATE(AFMT_VBI_PACKET_CONTROL, AFMT_GENERIC_CONFLICT_CLR, 1);
	}
	/* choose which generic packet to use */
	{
		regval = REG_READ(AFMT_VBI_PACKET_CONTROL);
		REG_UPDATE(AFMT_VBI_PACKET_CONTROL,
				AFMT_GENERIC_INDEX, packet_index);
	}

	/* write generic packet header
	 * (4th byte is for GENERIC0 only) */
	{
		REG_SET_4(AFMT_GENERIC_HDR, 0,
				AFMT_GENERIC_HB0, info_packet->hb0,
				AFMT_GENERIC_HB1, info_packet->hb1,
				AFMT_GENERIC_HB2, info_packet->hb2,
				AFMT_GENERIC_HB3, info_packet->hb3);
	}

	/* write generic packet contents
	 * (we never use last 4 bytes)
	 * there are 8 (0-7) mmDIG0_AFMT_GENERIC0_x registers */
	{
		const uint32_t *content =
			(const uint32_t *) &info_packet->sb[0];

		REG_WRITE(AFMT_GENERIC_0, *content++);
		REG_WRITE(AFMT_GENERIC_1, *content++);
		REG_WRITE(AFMT_GENERIC_2, *content++);
		REG_WRITE(AFMT_GENERIC_3, *content++);
		REG_WRITE(AFMT_GENERIC_4, *content++);
		REG_WRITE(AFMT_GENERIC_5, *content++);
		REG_WRITE(AFMT_GENERIC_6, *content++);
		REG_WRITE(AFMT_GENERIC_7, *content);
	}

	if (!REG(AFMT_VBI_PACKET_CONTROL1)) {
		/* force double-buffered packet update */
		REG_UPDATE_2(AFMT_VBI_PACKET_CONTROL,
			AFMT_GENERIC0_UPDATE, (packet_index == 0),
			AFMT_GENERIC2_UPDATE, (packet_index == 2));
	}
#if defined(CONFIG_DRM_AMD_DC_DCN1_0)
	if (REG(AFMT_VBI_PACKET_CONTROL1)) {
		switch (packet_index) {
		case 0:
			REG_UPDATE(AFMT_VBI_PACKET_CONTROL1,
					AFMT_GENERIC0_FRAME_UPDATE, 1);
			break;
		case 1:
			REG_UPDATE(AFMT_VBI_PACKET_CONTROL1,
					AFMT_GENERIC1_FRAME_UPDATE, 1);
			break;
		case 2:
			REG_UPDATE(AFMT_VBI_PACKET_CONTROL1,
					AFMT_GENERIC2_FRAME_UPDATE, 1);
			break;
		case 3:
			REG_UPDATE(AFMT_VBI_PACKET_CONTROL1,
					AFMT_GENERIC3_FRAME_UPDATE, 1);
			break;
		case 4:
			REG_UPDATE(AFMT_VBI_PACKET_CONTROL1,
					AFMT_GENERIC4_FRAME_UPDATE, 1);
			break;
		case 5:
			REG_UPDATE(AFMT_VBI_PACKET_CONTROL1,
					AFMT_GENERIC5_FRAME_UPDATE, 1);
			break;
		case 6:
			REG_UPDATE(AFMT_VBI_PACKET_CONTROL1,
					AFMT_GENERIC6_FRAME_UPDATE, 1);
			break;
		case 7:
			REG_UPDATE(AFMT_VBI_PACKET_CONTROL1,
					AFMT_GENERIC7_FRAME_UPDATE, 1);
			break;
		default:
			break;
		}
	}
#endif
}