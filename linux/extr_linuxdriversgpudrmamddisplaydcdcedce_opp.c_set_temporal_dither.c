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
struct dce110_opp {int dummy; } ;
struct TYPE_2__ {scalar_t__ FRAME_MODULATION_ENABLED; int FRAME_MODULATION_DEPTH; int TEMPORAL_LEVEL; int FRC25; int /*<<< orphan*/  FRC75; int /*<<< orphan*/  FRC50; } ;
struct bit_depth_reduction_params {TYPE_1__ flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  FMT_25FRC_SEL ; 
 int /*<<< orphan*/  FMT_50FRC_SEL ; 
 int /*<<< orphan*/  FMT_75FRC_SEL ; 
 int /*<<< orphan*/  FMT_BIT_DEPTH_CONTROL ; 
 int /*<<< orphan*/  FMT_TEMPORAL_DITHER_DEPTH ; 
 int /*<<< orphan*/  FMT_TEMPORAL_DITHER_EN ; 
 int /*<<< orphan*/  FMT_TEMPORAL_DITHER_OFFSET ; 
 int /*<<< orphan*/  FMT_TEMPORAL_DITHER_PATTERN_CONTROL ; 
 int /*<<< orphan*/  FMT_TEMPORAL_DITHER_PROGRAMMABLE_PATTERN_S_MATRIX ; 
 int /*<<< orphan*/  FMT_TEMPORAL_DITHER_PROGRAMMABLE_PATTERN_T_MATRIX ; 
 int /*<<< orphan*/  FMT_TEMPORAL_DITHER_RESET ; 
 int /*<<< orphan*/  FMT_TEMPORAL_LEVEL ; 
 scalar_t__ REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_UPDATE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  REG_UPDATE_2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_UPDATE_3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void set_temporal_dither(
	struct dce110_opp *opp110,
	const struct bit_depth_reduction_params *params)
{
	/*Disable temporal (frame modulation) dithering first*/
	REG_UPDATE_3(FMT_BIT_DEPTH_CONTROL,
		FMT_TEMPORAL_DITHER_EN, 0,
		FMT_TEMPORAL_DITHER_RESET, 0,
		FMT_TEMPORAL_DITHER_OFFSET, 0);

	REG_UPDATE_2(FMT_BIT_DEPTH_CONTROL,
		FMT_TEMPORAL_DITHER_DEPTH, 0,
		FMT_TEMPORAL_LEVEL, 0);

	REG_UPDATE_3(FMT_BIT_DEPTH_CONTROL,
		FMT_25FRC_SEL, 0,
		FMT_50FRC_SEL, 0,
		FMT_75FRC_SEL, 0);

	/* no 10bpc dither on DCE11*/
	if (params->flags.FRAME_MODULATION_ENABLED == 0 ||
		params->flags.FRAME_MODULATION_DEPTH == 2)
		return;

	/* Set temporal dithering depth*/
	REG_UPDATE_3(FMT_BIT_DEPTH_CONTROL,
		FMT_TEMPORAL_DITHER_DEPTH, params->flags.FRAME_MODULATION_DEPTH,
		FMT_TEMPORAL_DITHER_RESET, 0,
		FMT_TEMPORAL_DITHER_OFFSET, 0);

	/*Select legacy pattern based on FRC and Temporal level*/
	if (REG(FMT_TEMPORAL_DITHER_PATTERN_CONTROL)) {
		REG_WRITE(FMT_TEMPORAL_DITHER_PATTERN_CONTROL, 0);
		/*Set s matrix*/
		REG_WRITE(FMT_TEMPORAL_DITHER_PROGRAMMABLE_PATTERN_S_MATRIX, 0);
		/*Set t matrix*/
		REG_WRITE(FMT_TEMPORAL_DITHER_PROGRAMMABLE_PATTERN_T_MATRIX, 0);
	}

	/*Select patterns for 0.25, 0.5 and 0.75 grey level*/
	REG_UPDATE(FMT_BIT_DEPTH_CONTROL,
		FMT_TEMPORAL_LEVEL, params->flags.TEMPORAL_LEVEL);

	REG_UPDATE_3(FMT_BIT_DEPTH_CONTROL,
		FMT_25FRC_SEL, params->flags.FRC25,
		FMT_50FRC_SEL, params->flags.FRC50,
		FMT_75FRC_SEL, params->flags.FRC75);

	/*Enable bit reduction by temporal (frame modulation) dithering*/
	REG_UPDATE(FMT_BIT_DEPTH_CONTROL,
		FMT_TEMPORAL_DITHER_EN, 1);
}