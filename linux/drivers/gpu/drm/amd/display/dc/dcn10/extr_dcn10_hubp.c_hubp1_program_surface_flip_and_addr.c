#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_9__ ;
typedef  struct TYPE_25__   TYPE_8__ ;
typedef  struct TYPE_24__   TYPE_7__ ;
typedef  struct TYPE_23__   TYPE_6__ ;
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;
typedef  struct TYPE_17__   TYPE_13__ ;
typedef  struct TYPE_16__   TYPE_12__ ;
typedef  struct TYPE_15__   TYPE_11__ ;
typedef  struct TYPE_14__   TYPE_10__ ;

/* Type definitions */
struct TYPE_16__ {int /*<<< orphan*/  low_part; int /*<<< orphan*/  high_part; int /*<<< orphan*/  quad_part; } ;
struct TYPE_15__ {int /*<<< orphan*/  low_part; int /*<<< orphan*/  high_part; int /*<<< orphan*/  quad_part; } ;
struct TYPE_14__ {int /*<<< orphan*/  low_part; int /*<<< orphan*/  high_part; int /*<<< orphan*/  quad_part; } ;
struct TYPE_26__ {int /*<<< orphan*/  low_part; int /*<<< orphan*/  high_part; int /*<<< orphan*/  quad_part; } ;
struct TYPE_17__ {TYPE_12__ left_addr; TYPE_11__ right_addr; TYPE_10__ left_meta_addr; TYPE_9__ right_meta_addr; } ;
struct TYPE_24__ {int /*<<< orphan*/  low_part; int /*<<< orphan*/  high_part; int /*<<< orphan*/  quad_part; } ;
struct TYPE_23__ {int /*<<< orphan*/  low_part; int /*<<< orphan*/  high_part; int /*<<< orphan*/  quad_part; } ;
struct TYPE_22__ {int /*<<< orphan*/  low_part; int /*<<< orphan*/  high_part; int /*<<< orphan*/  quad_part; } ;
struct TYPE_21__ {int /*<<< orphan*/  low_part; int /*<<< orphan*/  high_part; } ;
struct TYPE_25__ {TYPE_7__ luma_addr; TYPE_6__ chroma_addr; TYPE_5__ luma_meta_addr; TYPE_4__ chroma_meta_addr; } ;
struct TYPE_19__ {int /*<<< orphan*/  low_part; int /*<<< orphan*/  high_part; int /*<<< orphan*/  quad_part; } ;
struct TYPE_18__ {int /*<<< orphan*/  low_part; int /*<<< orphan*/  high_part; int /*<<< orphan*/  quad_part; } ;
struct TYPE_20__ {TYPE_2__ addr; TYPE_1__ meta_addr; } ;
struct dc_plane_address {int type; TYPE_13__ grph_stereo; int /*<<< orphan*/  tmz_surface; TYPE_8__ video_progressive; TYPE_3__ grph; } ;
struct hubp {struct dc_plane_address request_address; } ;
struct dcn10_hubp {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BREAK_TO_DEBUGGER () ; 
 int /*<<< orphan*/  DCSURF_FLIP_CONTROL ; 
 int /*<<< orphan*/  DCSURF_PRIMARY_META_SURFACE_ADDRESS ; 
 int /*<<< orphan*/  DCSURF_PRIMARY_META_SURFACE_ADDRESS_C ; 
 int /*<<< orphan*/  DCSURF_PRIMARY_META_SURFACE_ADDRESS_HIGH ; 
 int /*<<< orphan*/  DCSURF_PRIMARY_META_SURFACE_ADDRESS_HIGH_C ; 
 int /*<<< orphan*/  DCSURF_PRIMARY_SURFACE_ADDRESS ; 
 int /*<<< orphan*/  DCSURF_PRIMARY_SURFACE_ADDRESS_C ; 
 int /*<<< orphan*/  DCSURF_PRIMARY_SURFACE_ADDRESS_HIGH ; 
 int /*<<< orphan*/  DCSURF_PRIMARY_SURFACE_ADDRESS_HIGH_C ; 
 int /*<<< orphan*/  DCSURF_SECONDARY_META_SURFACE_ADDRESS ; 
 int /*<<< orphan*/  DCSURF_SECONDARY_META_SURFACE_ADDRESS_HIGH ; 
 int /*<<< orphan*/  DCSURF_SECONDARY_SURFACE_ADDRESS ; 
 int /*<<< orphan*/  DCSURF_SECONDARY_SURFACE_ADDRESS_HIGH ; 
 int /*<<< orphan*/  DCSURF_SURFACE_CONTROL ; 
#define  PLN_ADDR_TYPE_GRAPHICS 130 
#define  PLN_ADDR_TYPE_GRPH_STEREO 129 
#define  PLN_ADDR_TYPE_VIDEO_PROGRESSIVE 128 
 int /*<<< orphan*/  PRIMARY_META_SURFACE_ADDRESS ; 
 int /*<<< orphan*/  PRIMARY_META_SURFACE_ADDRESS_C ; 
 int /*<<< orphan*/  PRIMARY_META_SURFACE_ADDRESS_HIGH ; 
 int /*<<< orphan*/  PRIMARY_META_SURFACE_ADDRESS_HIGH_C ; 
 int /*<<< orphan*/  PRIMARY_META_SURFACE_TMZ ; 
 int /*<<< orphan*/  PRIMARY_META_SURFACE_TMZ_C ; 
 int /*<<< orphan*/  PRIMARY_SURFACE_ADDRESS ; 
 int /*<<< orphan*/  PRIMARY_SURFACE_ADDRESS_C ; 
 int /*<<< orphan*/  PRIMARY_SURFACE_ADDRESS_HIGH ; 
 int /*<<< orphan*/  PRIMARY_SURFACE_ADDRESS_HIGH_C ; 
 int /*<<< orphan*/  PRIMARY_SURFACE_TMZ ; 
 int /*<<< orphan*/  PRIMARY_SURFACE_TMZ_C ; 
 int /*<<< orphan*/  REG_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_UPDATE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  REG_UPDATE_2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_UPDATE_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_UPDATE_8 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SECONDARY_META_SURFACE_ADDRESS ; 
 int /*<<< orphan*/  SECONDARY_META_SURFACE_ADDRESS_HIGH ; 
 int /*<<< orphan*/  SECONDARY_META_SURFACE_TMZ ; 
 int /*<<< orphan*/  SECONDARY_META_SURFACE_TMZ_C ; 
 int /*<<< orphan*/  SECONDARY_SURFACE_ADDRESS ; 
 int /*<<< orphan*/  SECONDARY_SURFACE_ADDRESS_HIGH ; 
 int /*<<< orphan*/  SECONDARY_SURFACE_TMZ ; 
 int /*<<< orphan*/  SECONDARY_SURFACE_TMZ_C ; 
 int /*<<< orphan*/  SURFACE_FLIP_IN_STEREOSYNC ; 
 int /*<<< orphan*/  SURFACE_FLIP_MODE_FOR_STEREOSYNC ; 
 int /*<<< orphan*/  SURFACE_FLIP_TYPE ; 
 struct dcn10_hubp* TO_DCN10_HUBP (struct hubp*) ; 

bool hubp1_program_surface_flip_and_addr(
	struct hubp *hubp,
	const struct dc_plane_address *address,
	bool flip_immediate)
{
	struct dcn10_hubp *hubp1 = TO_DCN10_HUBP(hubp);


	//program flip type
	REG_UPDATE(DCSURF_FLIP_CONTROL,
			SURFACE_FLIP_TYPE, flip_immediate);


	if (address->type == PLN_ADDR_TYPE_GRPH_STEREO) {
		REG_UPDATE(DCSURF_FLIP_CONTROL, SURFACE_FLIP_MODE_FOR_STEREOSYNC, 0x1);
		REG_UPDATE(DCSURF_FLIP_CONTROL, SURFACE_FLIP_IN_STEREOSYNC, 0x1);

	} else {
		// turn off stereo if not in stereo
		REG_UPDATE(DCSURF_FLIP_CONTROL, SURFACE_FLIP_MODE_FOR_STEREOSYNC, 0x0);
		REG_UPDATE(DCSURF_FLIP_CONTROL, SURFACE_FLIP_IN_STEREOSYNC, 0x0);
	}



	/* HW automatically latch rest of address register on write to
	 * DCSURF_PRIMARY_SURFACE_ADDRESS if SURFACE_UPDATE_LOCK is not used
	 *
	 * program high first and then the low addr, order matters!
	 */
	switch (address->type) {
	case PLN_ADDR_TYPE_GRAPHICS:
		/* DCN1.0 does not support const color
		 * TODO: program DCHUBBUB_RET_PATH_DCC_CFGx_0/1
		 * base on address->grph.dcc_const_color
		 * x = 0, 2, 4, 6 for pipe 0, 1, 2, 3 for rgb and luma
		 * x = 1, 3, 5, 7 for pipe 0, 1, 2, 3 for chroma
		 */

		if (address->grph.addr.quad_part == 0)
			break;

		REG_UPDATE_2(DCSURF_SURFACE_CONTROL,
				PRIMARY_SURFACE_TMZ, address->tmz_surface,
				PRIMARY_META_SURFACE_TMZ, address->tmz_surface);

		if (address->grph.meta_addr.quad_part != 0) {
			REG_SET(DCSURF_PRIMARY_META_SURFACE_ADDRESS_HIGH, 0,
					PRIMARY_META_SURFACE_ADDRESS_HIGH,
					address->grph.meta_addr.high_part);

			REG_SET(DCSURF_PRIMARY_META_SURFACE_ADDRESS, 0,
					PRIMARY_META_SURFACE_ADDRESS,
					address->grph.meta_addr.low_part);
		}

		REG_SET(DCSURF_PRIMARY_SURFACE_ADDRESS_HIGH, 0,
				PRIMARY_SURFACE_ADDRESS_HIGH,
				address->grph.addr.high_part);

		REG_SET(DCSURF_PRIMARY_SURFACE_ADDRESS, 0,
				PRIMARY_SURFACE_ADDRESS,
				address->grph.addr.low_part);
		break;
	case PLN_ADDR_TYPE_VIDEO_PROGRESSIVE:
		if (address->video_progressive.luma_addr.quad_part == 0
			|| address->video_progressive.chroma_addr.quad_part == 0)
			break;

		REG_UPDATE_4(DCSURF_SURFACE_CONTROL,
				PRIMARY_SURFACE_TMZ, address->tmz_surface,
				PRIMARY_SURFACE_TMZ_C, address->tmz_surface,
				PRIMARY_META_SURFACE_TMZ, address->tmz_surface,
				PRIMARY_META_SURFACE_TMZ_C, address->tmz_surface);

		if (address->video_progressive.luma_meta_addr.quad_part != 0) {
			REG_SET(DCSURF_PRIMARY_META_SURFACE_ADDRESS_HIGH_C, 0,
				PRIMARY_META_SURFACE_ADDRESS_HIGH_C,
				address->video_progressive.chroma_meta_addr.high_part);

			REG_SET(DCSURF_PRIMARY_META_SURFACE_ADDRESS_C, 0,
				PRIMARY_META_SURFACE_ADDRESS_C,
				address->video_progressive.chroma_meta_addr.low_part);

			REG_SET(DCSURF_PRIMARY_META_SURFACE_ADDRESS_HIGH, 0,
				PRIMARY_META_SURFACE_ADDRESS_HIGH,
				address->video_progressive.luma_meta_addr.high_part);

			REG_SET(DCSURF_PRIMARY_META_SURFACE_ADDRESS, 0,
				PRIMARY_META_SURFACE_ADDRESS,
				address->video_progressive.luma_meta_addr.low_part);
		}

		REG_SET(DCSURF_PRIMARY_SURFACE_ADDRESS_HIGH_C, 0,
			PRIMARY_SURFACE_ADDRESS_HIGH_C,
			address->video_progressive.chroma_addr.high_part);

		REG_SET(DCSURF_PRIMARY_SURFACE_ADDRESS_C, 0,
			PRIMARY_SURFACE_ADDRESS_C,
			address->video_progressive.chroma_addr.low_part);

		REG_SET(DCSURF_PRIMARY_SURFACE_ADDRESS_HIGH, 0,
			PRIMARY_SURFACE_ADDRESS_HIGH,
			address->video_progressive.luma_addr.high_part);

		REG_SET(DCSURF_PRIMARY_SURFACE_ADDRESS, 0,
			PRIMARY_SURFACE_ADDRESS,
			address->video_progressive.luma_addr.low_part);
		break;
	case PLN_ADDR_TYPE_GRPH_STEREO:
		if (address->grph_stereo.left_addr.quad_part == 0)
			break;
		if (address->grph_stereo.right_addr.quad_part == 0)
			break;

		REG_UPDATE_8(DCSURF_SURFACE_CONTROL,
				PRIMARY_SURFACE_TMZ, address->tmz_surface,
				PRIMARY_SURFACE_TMZ_C, address->tmz_surface,
				PRIMARY_META_SURFACE_TMZ, address->tmz_surface,
				PRIMARY_META_SURFACE_TMZ_C, address->tmz_surface,
				SECONDARY_SURFACE_TMZ, address->tmz_surface,
				SECONDARY_SURFACE_TMZ_C, address->tmz_surface,
				SECONDARY_META_SURFACE_TMZ, address->tmz_surface,
				SECONDARY_META_SURFACE_TMZ_C, address->tmz_surface);

		if (address->grph_stereo.right_meta_addr.quad_part != 0) {

			REG_SET(DCSURF_SECONDARY_META_SURFACE_ADDRESS_HIGH, 0,
					SECONDARY_META_SURFACE_ADDRESS_HIGH,
					address->grph_stereo.right_meta_addr.high_part);

			REG_SET(DCSURF_SECONDARY_META_SURFACE_ADDRESS, 0,
					SECONDARY_META_SURFACE_ADDRESS,
					address->grph_stereo.right_meta_addr.low_part);
		}
		if (address->grph_stereo.left_meta_addr.quad_part != 0) {

			REG_SET(DCSURF_PRIMARY_META_SURFACE_ADDRESS_HIGH, 0,
					PRIMARY_META_SURFACE_ADDRESS_HIGH,
					address->grph_stereo.left_meta_addr.high_part);

			REG_SET(DCSURF_PRIMARY_META_SURFACE_ADDRESS, 0,
					PRIMARY_META_SURFACE_ADDRESS,
					address->grph_stereo.left_meta_addr.low_part);
		}

		REG_SET(DCSURF_SECONDARY_SURFACE_ADDRESS_HIGH, 0,
				SECONDARY_SURFACE_ADDRESS_HIGH,
				address->grph_stereo.right_addr.high_part);

		REG_SET(DCSURF_SECONDARY_SURFACE_ADDRESS, 0,
				SECONDARY_SURFACE_ADDRESS,
				address->grph_stereo.right_addr.low_part);

		REG_SET(DCSURF_PRIMARY_SURFACE_ADDRESS_HIGH, 0,
				PRIMARY_SURFACE_ADDRESS_HIGH,
				address->grph_stereo.left_addr.high_part);

		REG_SET(DCSURF_PRIMARY_SURFACE_ADDRESS, 0,
				PRIMARY_SURFACE_ADDRESS,
				address->grph_stereo.left_addr.low_part);
		break;
	default:
		BREAK_TO_DEBUGGER();
		break;
	}

	hubp->request_address = *address;

	return true;
}