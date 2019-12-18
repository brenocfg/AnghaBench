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
struct pll_value {scalar_t__ clockType; } ;
struct mode_parameter {int horizontal_total; int horizontal_display_end; unsigned int horizontal_sync_width; int horizontal_sync_start; int vertical_total; int vertical_display_end; unsigned int vertical_sync_height; int vertical_sync_start; scalar_t__ clock_phase_polarity; scalar_t__ horizontal_sync_polarity; scalar_t__ vertical_sync_polarity; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRT_DISPLAY_CTRL ; 
 int /*<<< orphan*/  CRT_HORIZONTAL_SYNC ; 
 int CRT_HORIZONTAL_SYNC_START_MASK ; 
 unsigned int CRT_HORIZONTAL_SYNC_WIDTH_MASK ; 
 unsigned int CRT_HORIZONTAL_SYNC_WIDTH_SHIFT ; 
 int /*<<< orphan*/  CRT_HORIZONTAL_TOTAL ; 
 int CRT_HORIZONTAL_TOTAL_DISPLAY_END_MASK ; 
 int CRT_HORIZONTAL_TOTAL_TOTAL_MASK ; 
 int CRT_HORIZONTAL_TOTAL_TOTAL_SHIFT ; 
 int /*<<< orphan*/  CRT_PLL_CTRL ; 
 int /*<<< orphan*/  CRT_VERTICAL_SYNC ; 
 unsigned int CRT_VERTICAL_SYNC_HEIGHT_MASK ; 
 unsigned int CRT_VERTICAL_SYNC_HEIGHT_SHIFT ; 
 int CRT_VERTICAL_SYNC_START_MASK ; 
 int /*<<< orphan*/  CRT_VERTICAL_TOTAL ; 
 int CRT_VERTICAL_TOTAL_DISPLAY_END_MASK ; 
 int CRT_VERTICAL_TOTAL_TOTAL_MASK ; 
 int CRT_VERTICAL_TOTAL_TOTAL_SHIFT ; 
 unsigned int DISPLAY_CTRL_CLOCK_PHASE ; 
 unsigned int DISPLAY_CTRL_HSYNC_PHASE ; 
 unsigned int DISPLAY_CTRL_PLANE ; 
 unsigned int DISPLAY_CTRL_TIMING ; 
 unsigned int DISPLAY_CTRL_VSYNC_PHASE ; 
 int /*<<< orphan*/  PANEL_DISPLAY_CTRL ; 
 unsigned int PANEL_DISPLAY_CTRL_RESERVED_MASK ; 
 unsigned int PANEL_DISPLAY_CTRL_VSYNC ; 
 int /*<<< orphan*/  PANEL_HORIZONTAL_SYNC ; 
 int PANEL_HORIZONTAL_SYNC_START_MASK ; 
 int PANEL_HORIZONTAL_SYNC_WIDTH_MASK ; 
 int PANEL_HORIZONTAL_SYNC_WIDTH_SHIFT ; 
 int /*<<< orphan*/  PANEL_HORIZONTAL_TOTAL ; 
 int PANEL_HORIZONTAL_TOTAL_DISPLAY_END_MASK ; 
 int PANEL_HORIZONTAL_TOTAL_TOTAL_MASK ; 
 int PANEL_HORIZONTAL_TOTAL_TOTAL_SHIFT ; 
 int /*<<< orphan*/  PANEL_PLL_CTRL ; 
 int /*<<< orphan*/  PANEL_VERTICAL_SYNC ; 
 int PANEL_VERTICAL_SYNC_HEIGHT_MASK ; 
 int PANEL_VERTICAL_SYNC_HEIGHT_SHIFT ; 
 int PANEL_VERTICAL_SYNC_START_MASK ; 
 int /*<<< orphan*/  PANEL_VERTICAL_TOTAL ; 
 int PANEL_VERTICAL_TOTAL_DISPLAY_END_MASK ; 
 int PANEL_VERTICAL_TOTAL_TOTAL_MASK ; 
 int PANEL_VERTICAL_TOTAL_TOTAL_SHIFT ; 
 scalar_t__ PRIMARY_PLL ; 
 scalar_t__ SECONDARY_PLL ; 
 scalar_t__ SM750LE ; 
 int /*<<< orphan*/  displayControlAdjust_SM750LE (struct mode_parameter*,unsigned int) ; 
 unsigned int peek32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  poke32 (int /*<<< orphan*/ ,unsigned int) ; 
 unsigned int sm750_format_pll_reg (struct pll_value*) ; 
 scalar_t__ sm750_get_chip_type () ; 

__attribute__((used)) static int programModeRegisters(struct mode_parameter *pModeParam,
				struct pll_value *pll)
{
	int ret = 0;
	int cnt = 0;
	unsigned int tmp, reg;

	if (pll->clockType == SECONDARY_PLL) {
		/* programe secondary pixel clock */
		poke32(CRT_PLL_CTRL, sm750_format_pll_reg(pll));

		tmp = ((pModeParam->horizontal_total - 1) <<
		       CRT_HORIZONTAL_TOTAL_TOTAL_SHIFT) &
		     CRT_HORIZONTAL_TOTAL_TOTAL_MASK;
		tmp |= (pModeParam->horizontal_display_end - 1) &
		      CRT_HORIZONTAL_TOTAL_DISPLAY_END_MASK;

		poke32(CRT_HORIZONTAL_TOTAL, tmp);

		tmp = (pModeParam->horizontal_sync_width <<
		       CRT_HORIZONTAL_SYNC_WIDTH_SHIFT) &
		     CRT_HORIZONTAL_SYNC_WIDTH_MASK;
		tmp |= (pModeParam->horizontal_sync_start - 1) &
		      CRT_HORIZONTAL_SYNC_START_MASK;

		poke32(CRT_HORIZONTAL_SYNC, tmp);

		tmp = ((pModeParam->vertical_total - 1) <<
		       CRT_VERTICAL_TOTAL_TOTAL_SHIFT) &
		     CRT_VERTICAL_TOTAL_TOTAL_MASK;
		tmp |= (pModeParam->vertical_display_end - 1) &
		      CRT_VERTICAL_TOTAL_DISPLAY_END_MASK;

		poke32(CRT_VERTICAL_TOTAL, tmp);

		tmp = ((pModeParam->vertical_sync_height <<
		       CRT_VERTICAL_SYNC_HEIGHT_SHIFT)) &
		     CRT_VERTICAL_SYNC_HEIGHT_MASK;
		tmp |= (pModeParam->vertical_sync_start - 1) &
		      CRT_VERTICAL_SYNC_START_MASK;

		poke32(CRT_VERTICAL_SYNC, tmp);

		tmp = DISPLAY_CTRL_TIMING | DISPLAY_CTRL_PLANE;
		if (pModeParam->vertical_sync_polarity)
			tmp |= DISPLAY_CTRL_VSYNC_PHASE;
		if (pModeParam->horizontal_sync_polarity)
			tmp |= DISPLAY_CTRL_HSYNC_PHASE;

		if (sm750_get_chip_type() == SM750LE) {
			displayControlAdjust_SM750LE(pModeParam, tmp);
		} else {
			reg = peek32(CRT_DISPLAY_CTRL) &
				~(DISPLAY_CTRL_VSYNC_PHASE |
				  DISPLAY_CTRL_HSYNC_PHASE |
				  DISPLAY_CTRL_TIMING | DISPLAY_CTRL_PLANE);

			poke32(CRT_DISPLAY_CTRL, tmp | reg);
		}

	} else if (pll->clockType == PRIMARY_PLL) {
		unsigned int reserved;

		poke32(PANEL_PLL_CTRL, sm750_format_pll_reg(pll));

		reg = ((pModeParam->horizontal_total - 1) <<
			PANEL_HORIZONTAL_TOTAL_TOTAL_SHIFT) &
			PANEL_HORIZONTAL_TOTAL_TOTAL_MASK;
		reg |= ((pModeParam->horizontal_display_end - 1) &
			PANEL_HORIZONTAL_TOTAL_DISPLAY_END_MASK);
		poke32(PANEL_HORIZONTAL_TOTAL, reg);

		poke32(PANEL_HORIZONTAL_SYNC,
		       ((pModeParam->horizontal_sync_width <<
			 PANEL_HORIZONTAL_SYNC_WIDTH_SHIFT) &
			PANEL_HORIZONTAL_SYNC_WIDTH_MASK) |
		       ((pModeParam->horizontal_sync_start - 1) &
			PANEL_HORIZONTAL_SYNC_START_MASK));

		poke32(PANEL_VERTICAL_TOTAL,
		       (((pModeParam->vertical_total - 1) <<
			 PANEL_VERTICAL_TOTAL_TOTAL_SHIFT) &
			PANEL_VERTICAL_TOTAL_TOTAL_MASK) |
		       ((pModeParam->vertical_display_end - 1) &
			PANEL_VERTICAL_TOTAL_DISPLAY_END_MASK));

		poke32(PANEL_VERTICAL_SYNC,
		       ((pModeParam->vertical_sync_height <<
			 PANEL_VERTICAL_SYNC_HEIGHT_SHIFT) &
			PANEL_VERTICAL_SYNC_HEIGHT_MASK) |
		       ((pModeParam->vertical_sync_start - 1) &
			PANEL_VERTICAL_SYNC_START_MASK));

		tmp = DISPLAY_CTRL_TIMING | DISPLAY_CTRL_PLANE;
		if (pModeParam->vertical_sync_polarity)
			tmp |= DISPLAY_CTRL_VSYNC_PHASE;
		if (pModeParam->horizontal_sync_polarity)
			tmp |= DISPLAY_CTRL_HSYNC_PHASE;
		if (pModeParam->clock_phase_polarity)
			tmp |= DISPLAY_CTRL_CLOCK_PHASE;

		reserved = PANEL_DISPLAY_CTRL_RESERVED_MASK |
			PANEL_DISPLAY_CTRL_VSYNC;

		reg = (peek32(PANEL_DISPLAY_CTRL) & ~reserved) &
			~(DISPLAY_CTRL_CLOCK_PHASE | DISPLAY_CTRL_VSYNC_PHASE |
			  DISPLAY_CTRL_HSYNC_PHASE | DISPLAY_CTRL_TIMING |
			  DISPLAY_CTRL_PLANE);

		/*
		 * May a hardware bug or just my test chip (not confirmed).
		 * PANEL_DISPLAY_CTRL register seems requiring few writes
		 * before a value can be successfully written in.
		 * Added some masks to mask out the reserved bits.
		 * Note: This problem happens by design. The hardware will wait
		 *       for the next vertical sync to turn on/off the plane.
		 */
		poke32(PANEL_DISPLAY_CTRL, tmp | reg);

		while ((peek32(PANEL_DISPLAY_CTRL) & ~reserved) !=
			(tmp | reg)) {
			cnt++;
			if (cnt > 1000)
				break;
			poke32(PANEL_DISPLAY_CTRL, tmp | reg);
		}
	} else {
		ret = -1;
	}
	return ret;
}