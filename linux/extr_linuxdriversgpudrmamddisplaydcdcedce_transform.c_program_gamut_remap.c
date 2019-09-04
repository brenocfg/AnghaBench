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
typedef  int /*<<< orphan*/  uint16_t ;
struct dce_transform {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GAMUT_REMAP_C11 ; 
 int /*<<< orphan*/  GAMUT_REMAP_C11_C12 ; 
 int /*<<< orphan*/  GAMUT_REMAP_C12 ; 
 int /*<<< orphan*/  GAMUT_REMAP_C13 ; 
 int /*<<< orphan*/  GAMUT_REMAP_C13_C14 ; 
 int /*<<< orphan*/  GAMUT_REMAP_C14 ; 
 int /*<<< orphan*/  GAMUT_REMAP_C21 ; 
 int /*<<< orphan*/  GAMUT_REMAP_C21_C22 ; 
 int /*<<< orphan*/  GAMUT_REMAP_C22 ; 
 int /*<<< orphan*/  GAMUT_REMAP_C23 ; 
 int /*<<< orphan*/  GAMUT_REMAP_C23_C24 ; 
 int /*<<< orphan*/  GAMUT_REMAP_C24 ; 
 int /*<<< orphan*/  GAMUT_REMAP_C31 ; 
 int /*<<< orphan*/  GAMUT_REMAP_C31_C32 ; 
 int /*<<< orphan*/  GAMUT_REMAP_C32 ; 
 int /*<<< orphan*/  GAMUT_REMAP_C33 ; 
 int /*<<< orphan*/  GAMUT_REMAP_C33_C34 ; 
 int /*<<< orphan*/  GAMUT_REMAP_C34 ; 
 int /*<<< orphan*/  GAMUT_REMAP_CONTROL ; 
 int /*<<< orphan*/  GRPH_GAMUT_REMAP_MODE ; 
 int /*<<< orphan*/  REG_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  REG_SET_2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const,int /*<<< orphan*/ ,int /*<<< orphan*/  const) ; 

__attribute__((used)) static void program_gamut_remap(
	struct dce_transform *xfm_dce,
	const uint16_t *reg_val)
{
	if (reg_val) {
		REG_SET_2(GAMUT_REMAP_C11_C12, 0,
				GAMUT_REMAP_C11, reg_val[0],
				GAMUT_REMAP_C12, reg_val[1]);
		REG_SET_2(GAMUT_REMAP_C13_C14, 0,
				GAMUT_REMAP_C13, reg_val[2],
				GAMUT_REMAP_C14, reg_val[3]);
		REG_SET_2(GAMUT_REMAP_C21_C22, 0,
				GAMUT_REMAP_C21, reg_val[4],
				GAMUT_REMAP_C22, reg_val[5]);
		REG_SET_2(GAMUT_REMAP_C23_C24, 0,
				GAMUT_REMAP_C23, reg_val[6],
				GAMUT_REMAP_C24, reg_val[7]);
		REG_SET_2(GAMUT_REMAP_C31_C32, 0,
				GAMUT_REMAP_C31, reg_val[8],
				GAMUT_REMAP_C32, reg_val[9]);
		REG_SET_2(GAMUT_REMAP_C33_C34, 0,
				GAMUT_REMAP_C33, reg_val[10],
				GAMUT_REMAP_C34, reg_val[11]);

		REG_SET(GAMUT_REMAP_CONTROL, 0, GRPH_GAMUT_REMAP_MODE, 1);
	} else
		REG_SET(GAMUT_REMAP_CONTROL, 0, GRPH_GAMUT_REMAP_MODE, 0);

}