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
struct hubp {int dummy; } ;
struct dcn20_hubp {int dummy; } ;
typedef  enum dc_rotation_angle { ____Placeholder_dc_rotation_angle } dc_rotation_angle ;

/* Variables and functions */
 int /*<<< orphan*/  DCSURF_SURFACE_CONFIG ; 
 int /*<<< orphan*/  H_MIRROR_EN ; 
 int /*<<< orphan*/  REG_UPDATE_2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ROTATION_ANGLE ; 
 int ROTATION_ANGLE_0 ; 
 int ROTATION_ANGLE_180 ; 
 int ROTATION_ANGLE_270 ; 
 int ROTATION_ANGLE_90 ; 
 struct dcn20_hubp* TO_DCN20_HUBP (struct hubp*) ; 

void hubp2_program_rotation(
	struct hubp *hubp,
	enum dc_rotation_angle rotation,
	bool horizontal_mirror)
{
	struct dcn20_hubp *hubp2 = TO_DCN20_HUBP(hubp);
	uint32_t mirror;


	if (horizontal_mirror)
		mirror = 1;
	else
		mirror = 0;

	/* Program rotation angle and horz mirror - no mirror */
	if (rotation == ROTATION_ANGLE_0)
		REG_UPDATE_2(DCSURF_SURFACE_CONFIG,
				ROTATION_ANGLE, 0,
				H_MIRROR_EN, mirror);
	else if (rotation == ROTATION_ANGLE_90)
		REG_UPDATE_2(DCSURF_SURFACE_CONFIG,
				ROTATION_ANGLE, 1,
				H_MIRROR_EN, mirror);
	else if (rotation == ROTATION_ANGLE_180)
		REG_UPDATE_2(DCSURF_SURFACE_CONFIG,
				ROTATION_ANGLE, 2,
				H_MIRROR_EN, mirror);
	else if (rotation == ROTATION_ANGLE_270)
		REG_UPDATE_2(DCSURF_SURFACE_CONFIG,
				ROTATION_ANGLE, 3,
				H_MIRROR_EN, mirror);
}