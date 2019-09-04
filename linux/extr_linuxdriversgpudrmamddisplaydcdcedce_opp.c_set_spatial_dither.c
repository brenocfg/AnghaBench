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
struct dce110_opp {TYPE_1__* opp_mask; } ;
struct TYPE_4__ {scalar_t__ SPATIAL_DITHER_ENABLED; int SPATIAL_DITHER_DEPTH; int FRAME_RANDOM; int HIGHPASS_RANDOM; int RGB_RANDOM; int SPATIAL_DITHER_MODE; } ;
struct bit_depth_reduction_params {TYPE_2__ flags; int /*<<< orphan*/  b_seed_value; int /*<<< orphan*/  g_seed_value; int /*<<< orphan*/  r_seed_value; } ;
struct TYPE_3__ {scalar_t__ FMT_SPATIAL_DITHER_FRAME_COUNTER_BIT_SWAP; scalar_t__ FMT_SPATIAL_DITHER_FRAME_COUNTER_MAX; } ;

/* Variables and functions */
 int /*<<< orphan*/  FMT_BIT_DEPTH_CONTROL ; 
 int /*<<< orphan*/  FMT_CONTROL ; 
 int /*<<< orphan*/  FMT_DITHER_RAND_B_SEED ; 
 int /*<<< orphan*/  FMT_DITHER_RAND_G_SEED ; 
 int /*<<< orphan*/  FMT_DITHER_RAND_R_SEED ; 
 int /*<<< orphan*/  FMT_FRAME_RANDOM_ENABLE ; 
 int /*<<< orphan*/  FMT_HIGHPASS_RANDOM_ENABLE ; 
 int /*<<< orphan*/  FMT_RAND_B_SEED ; 
 int /*<<< orphan*/  FMT_RAND_G_SEED ; 
 int /*<<< orphan*/  FMT_RAND_R_SEED ; 
 int /*<<< orphan*/  FMT_RGB_RANDOM_ENABLE ; 
 int /*<<< orphan*/  FMT_SPATIAL_DITHER_DEPTH ; 
 int /*<<< orphan*/  FMT_SPATIAL_DITHER_EN ; 
 int /*<<< orphan*/  FMT_SPATIAL_DITHER_FRAME_COUNTER_BIT_SWAP ; 
 int /*<<< orphan*/  FMT_SPATIAL_DITHER_FRAME_COUNTER_MAX ; 
 int /*<<< orphan*/  FMT_SPATIAL_DITHER_MODE ; 
 int /*<<< orphan*/  FMT_TEMPORAL_DITHER_EN ; 
 int /*<<< orphan*/  REG_UPDATE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_UPDATE_2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  REG_UPDATE_3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void set_spatial_dither(
	struct dce110_opp *opp110,
	const struct bit_depth_reduction_params *params)
{
	/*Disable spatial (random) dithering*/
	REG_UPDATE_3(FMT_BIT_DEPTH_CONTROL,
		FMT_SPATIAL_DITHER_EN, 0,
		FMT_SPATIAL_DITHER_DEPTH, 0,
		FMT_SPATIAL_DITHER_MODE, 0);

	REG_UPDATE_3(FMT_BIT_DEPTH_CONTROL,
		FMT_HIGHPASS_RANDOM_ENABLE, 0,
		FMT_FRAME_RANDOM_ENABLE, 0,
		FMT_RGB_RANDOM_ENABLE, 0);

	REG_UPDATE(FMT_BIT_DEPTH_CONTROL,
		FMT_TEMPORAL_DITHER_EN, 0);

	/* no 10bpc on DCE11*/
	if (params->flags.SPATIAL_DITHER_ENABLED == 0 ||
		params->flags.SPATIAL_DITHER_DEPTH == 2)
		return;

	/* only use FRAME_COUNTER_MAX if frameRandom == 1*/

	if (opp110->opp_mask->FMT_SPATIAL_DITHER_FRAME_COUNTER_MAX &&
			opp110->opp_mask->FMT_SPATIAL_DITHER_FRAME_COUNTER_BIT_SWAP) {
		if (params->flags.FRAME_RANDOM == 1) {
			if (params->flags.SPATIAL_DITHER_DEPTH == 0 ||
			params->flags.SPATIAL_DITHER_DEPTH == 1) {
				REG_UPDATE_2(FMT_CONTROL,
					FMT_SPATIAL_DITHER_FRAME_COUNTER_MAX, 15,
					FMT_SPATIAL_DITHER_FRAME_COUNTER_BIT_SWAP, 2);
			} else if (params->flags.SPATIAL_DITHER_DEPTH == 2) {
				REG_UPDATE_2(FMT_CONTROL,
					FMT_SPATIAL_DITHER_FRAME_COUNTER_MAX, 3,
					FMT_SPATIAL_DITHER_FRAME_COUNTER_BIT_SWAP, 1);
			} else
				return;
		} else {
			REG_UPDATE_2(FMT_CONTROL,
					FMT_SPATIAL_DITHER_FRAME_COUNTER_MAX, 0,
					FMT_SPATIAL_DITHER_FRAME_COUNTER_BIT_SWAP, 0);
		}
	}
	/* Set seed for random values for
	 * spatial dithering for R,G,B channels
	 */
	REG_UPDATE(FMT_DITHER_RAND_R_SEED,
			FMT_RAND_R_SEED, params->r_seed_value);

	REG_UPDATE(FMT_DITHER_RAND_G_SEED,
			FMT_RAND_G_SEED, params->g_seed_value);

	REG_UPDATE(FMT_DITHER_RAND_B_SEED,
			FMT_RAND_B_SEED, params->b_seed_value);

	/* FMT_OFFSET_R_Cr  31:16 0x0 Setting the zero
	 * offset for the R/Cr channel, lower 4LSB
	 * is forced to zeros. Typically set to 0
	 * RGB and 0x80000 YCbCr.
	 */
	/* FMT_OFFSET_G_Y   31:16 0x0 Setting the zero
	 * offset for the G/Y  channel, lower 4LSB is
	 * forced to zeros. Typically set to 0 RGB
	 * and 0x80000 YCbCr.
	 */
	/* FMT_OFFSET_B_Cb  31:16 0x0 Setting the zero
	 * offset for the B/Cb channel, lower 4LSB is
	 * forced to zeros. Typically set to 0 RGB and
	 * 0x80000 YCbCr.
	 */

	/* Disable High pass filter
	 * Reset only at startup
	 * Set RGB data dithered with x^28+x^3+1
	 */
	REG_UPDATE_3(FMT_BIT_DEPTH_CONTROL,
		FMT_HIGHPASS_RANDOM_ENABLE, params->flags.HIGHPASS_RANDOM,
		FMT_FRAME_RANDOM_ENABLE, params->flags.FRAME_RANDOM,
		FMT_RGB_RANDOM_ENABLE, params->flags.RGB_RANDOM);

	/* Set spatial dithering bit depth
	 * Set spatial dithering mode
	 * (default is Seed patterrn AAAA...)
	 * Enable spatial dithering
	 */
	REG_UPDATE_3(FMT_BIT_DEPTH_CONTROL,
		FMT_SPATIAL_DITHER_DEPTH, params->flags.SPATIAL_DITHER_DEPTH,
		FMT_SPATIAL_DITHER_MODE, params->flags.SPATIAL_DITHER_MODE,
		FMT_SPATIAL_DITHER_EN, 1);
}