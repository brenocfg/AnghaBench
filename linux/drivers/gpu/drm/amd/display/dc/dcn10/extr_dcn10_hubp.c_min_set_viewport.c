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
struct rect {int /*<<< orphan*/  y; int /*<<< orphan*/  x; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct hubp {int dummy; } ;
struct dcn10_hubp {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DCSURF_PRI_VIEWPORT_DIMENSION ; 
 int /*<<< orphan*/  DCSURF_PRI_VIEWPORT_DIMENSION_C ; 
 int /*<<< orphan*/  DCSURF_PRI_VIEWPORT_START ; 
 int /*<<< orphan*/  DCSURF_PRI_VIEWPORT_START_C ; 
 int /*<<< orphan*/  DCSURF_SEC_VIEWPORT_DIMENSION ; 
 int /*<<< orphan*/  DCSURF_SEC_VIEWPORT_START ; 
 int /*<<< orphan*/  PRI_VIEWPORT_HEIGHT ; 
 int /*<<< orphan*/  PRI_VIEWPORT_HEIGHT_C ; 
 int /*<<< orphan*/  PRI_VIEWPORT_WIDTH ; 
 int /*<<< orphan*/  PRI_VIEWPORT_WIDTH_C ; 
 int /*<<< orphan*/  PRI_VIEWPORT_X_START ; 
 int /*<<< orphan*/  PRI_VIEWPORT_X_START_C ; 
 int /*<<< orphan*/  PRI_VIEWPORT_Y_START ; 
 int /*<<< orphan*/  PRI_VIEWPORT_Y_START_C ; 
 int /*<<< orphan*/  REG_SET_2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SEC_VIEWPORT_HEIGHT ; 
 int /*<<< orphan*/  SEC_VIEWPORT_WIDTH ; 
 int /*<<< orphan*/  SEC_VIEWPORT_X_START ; 
 int /*<<< orphan*/  SEC_VIEWPORT_Y_START ; 
 struct dcn10_hubp* TO_DCN10_HUBP (struct hubp*) ; 

void min_set_viewport(
	struct hubp *hubp,
	const struct rect *viewport,
	const struct rect *viewport_c)
{
	struct dcn10_hubp *hubp1 = TO_DCN10_HUBP(hubp);

	REG_SET_2(DCSURF_PRI_VIEWPORT_DIMENSION, 0,
		  PRI_VIEWPORT_WIDTH, viewport->width,
		  PRI_VIEWPORT_HEIGHT, viewport->height);

	REG_SET_2(DCSURF_PRI_VIEWPORT_START, 0,
		  PRI_VIEWPORT_X_START, viewport->x,
		  PRI_VIEWPORT_Y_START, viewport->y);

	/*for stereo*/
	REG_SET_2(DCSURF_SEC_VIEWPORT_DIMENSION, 0,
		  SEC_VIEWPORT_WIDTH, viewport->width,
		  SEC_VIEWPORT_HEIGHT, viewport->height);

	REG_SET_2(DCSURF_SEC_VIEWPORT_START, 0,
		  SEC_VIEWPORT_X_START, viewport->x,
		  SEC_VIEWPORT_Y_START, viewport->y);

	/* DC supports NV12 only at the moment */
	REG_SET_2(DCSURF_PRI_VIEWPORT_DIMENSION_C, 0,
		  PRI_VIEWPORT_WIDTH_C, viewport_c->width,
		  PRI_VIEWPORT_HEIGHT_C, viewport_c->height);

	REG_SET_2(DCSURF_PRI_VIEWPORT_START_C, 0,
		  PRI_VIEWPORT_X_START_C, viewport_c->x,
		  PRI_VIEWPORT_Y_START_C, viewport_c->y);
}