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
typedef  int u32 ;
struct lynx_accel {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DE_CLIP_BR ; 
 int /*<<< orphan*/  DE_CLIP_TL ; 
 int /*<<< orphan*/  DE_COLOR_COMPARE ; 
 int /*<<< orphan*/  DE_COLOR_COMPARE_MASK ; 
 int /*<<< orphan*/  DE_CONTROL ; 
 int DE_CONTROL_TRANSPARENCY ; 
 int DE_CONTROL_TRANSPARENCY_MATCH ; 
 int DE_CONTROL_TRANSPARENCY_SELECT ; 
 int /*<<< orphan*/  DE_MASKS ; 
 int /*<<< orphan*/  DE_STRETCH_FORMAT ; 
 int DE_STRETCH_FORMAT_ADDRESSING_MASK ; 
 int DE_STRETCH_FORMAT_PATTERN_XY ; 
 int DE_STRETCH_FORMAT_PATTERN_X_MASK ; 
 int DE_STRETCH_FORMAT_PATTERN_Y_MASK ; 
 int DE_STRETCH_FORMAT_SOURCE_HEIGHT_MASK ; 
 int read_dpr (struct lynx_accel*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_dpr (struct lynx_accel*,int /*<<< orphan*/ ,int) ; 

void sm750_hw_de_init(struct lynx_accel *accel)
{
	/* setup 2d engine registers */
	u32 reg, clr;

	write_dpr(accel, DE_MASKS, 0xFFFFFFFF);

	/* dpr1c */
	reg =  0x3;

	clr = DE_STRETCH_FORMAT_PATTERN_XY |
	      DE_STRETCH_FORMAT_PATTERN_Y_MASK |
	      DE_STRETCH_FORMAT_PATTERN_X_MASK |
	      DE_STRETCH_FORMAT_ADDRESSING_MASK |
	      DE_STRETCH_FORMAT_SOURCE_HEIGHT_MASK;

	/* DE_STRETCH bpp format need be initialized in setMode routine */
	write_dpr(accel, DE_STRETCH_FORMAT,
		  (read_dpr(accel, DE_STRETCH_FORMAT) & ~clr) | reg);

	/* disable clipping and transparent */
	write_dpr(accel, DE_CLIP_TL, 0); /* dpr2c */
	write_dpr(accel, DE_CLIP_BR, 0); /* dpr30 */

	write_dpr(accel, DE_COLOR_COMPARE_MASK, 0); /* dpr24 */
	write_dpr(accel, DE_COLOR_COMPARE, 0);

	clr = DE_CONTROL_TRANSPARENCY | DE_CONTROL_TRANSPARENCY_MATCH |
		DE_CONTROL_TRANSPARENCY_SELECT;

	/* dpr0c */
	write_dpr(accel, DE_CONTROL, read_dpr(accel, DE_CONTROL) & ~clr);
}