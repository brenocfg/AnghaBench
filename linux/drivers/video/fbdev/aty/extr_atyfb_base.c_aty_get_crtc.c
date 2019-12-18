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
struct crtc {int lcd_index; int lcd_gen_cntl; void* shadow_v_sync_strt_wid; void* shadow_v_tot_disp; void* shadow_h_sync_strt_wid; void* shadow_h_tot_disp; void* gen_cntl; void* off_pitch; void* vline_crnt_vline; void* v_sync_strt_wid; void* v_tot_disp; void* h_sync_strt_wid; void* h_tot_disp; void* ext_vert_stretch; void* vert_stretching; void* horz_stretching; void* lcd_config_panel; } ;
struct atyfb_par {scalar_t__ lcd_table; } ;

/* Variables and functions */
 int /*<<< orphan*/  CNFG_PANEL ; 
 int /*<<< orphan*/  CRTC_GEN_CNTL ; 
 int /*<<< orphan*/  CRTC_H_SYNC_STRT_WID ; 
 int /*<<< orphan*/  CRTC_H_TOTAL_DISP ; 
 int /*<<< orphan*/  CRTC_OFF_PITCH ; 
 int CRTC_RW_SELECT ; 
 int /*<<< orphan*/  CRTC_VLINE_CRNT_VLINE ; 
 int /*<<< orphan*/  CRTC_V_SYNC_STRT_WID ; 
 int /*<<< orphan*/  CRTC_V_TOTAL_DISP ; 
 int /*<<< orphan*/  EXT_VERT_STRETCH ; 
 int /*<<< orphan*/  HORZ_STRETCHING ; 
 int /*<<< orphan*/  LCD_GEN_CNTL ; 
 int /*<<< orphan*/  LCD_INDEX ; 
 int /*<<< orphan*/  LT_LCD_REGS ; 
 int /*<<< orphan*/  M64_HAS (int /*<<< orphan*/ ) ; 
 int SHADOW_EN ; 
 int SHADOW_RW_EN ; 
 int /*<<< orphan*/  VERT_STRETCHING ; 
 void* aty_ld_lcd (int /*<<< orphan*/ ,struct atyfb_par const*) ; 
 void* aty_ld_le32 (int /*<<< orphan*/ ,struct atyfb_par const*) ; 
 int /*<<< orphan*/  aty_st_lcd (int /*<<< orphan*/ ,int,struct atyfb_par const*) ; 
 int /*<<< orphan*/  aty_st_le32 (int /*<<< orphan*/ ,int,struct atyfb_par const*) ; 

__attribute__((used)) static void aty_get_crtc(const struct atyfb_par *par, struct crtc *crtc)
{
#ifdef CONFIG_FB_ATY_GENERIC_LCD
	if (par->lcd_table != 0) {
		if (!M64_HAS(LT_LCD_REGS)) {
			crtc->lcd_index = aty_ld_le32(LCD_INDEX, par);
			aty_st_le32(LCD_INDEX, crtc->lcd_index, par);
		}
		crtc->lcd_config_panel = aty_ld_lcd(CNFG_PANEL, par);
		crtc->lcd_gen_cntl = aty_ld_lcd(LCD_GEN_CNTL, par);


		/* switch to non shadow registers */
		aty_st_lcd(LCD_GEN_CNTL, crtc->lcd_gen_cntl &
			   ~(CRTC_RW_SELECT | SHADOW_EN | SHADOW_RW_EN), par);

		/* save stretching */
		crtc->horz_stretching = aty_ld_lcd(HORZ_STRETCHING, par);
		crtc->vert_stretching = aty_ld_lcd(VERT_STRETCHING, par);
		if (!M64_HAS(LT_LCD_REGS))
			crtc->ext_vert_stretch = aty_ld_lcd(EXT_VERT_STRETCH, par);
	}
#endif
	crtc->h_tot_disp = aty_ld_le32(CRTC_H_TOTAL_DISP, par);
	crtc->h_sync_strt_wid = aty_ld_le32(CRTC_H_SYNC_STRT_WID, par);
	crtc->v_tot_disp = aty_ld_le32(CRTC_V_TOTAL_DISP, par);
	crtc->v_sync_strt_wid = aty_ld_le32(CRTC_V_SYNC_STRT_WID, par);
	crtc->vline_crnt_vline = aty_ld_le32(CRTC_VLINE_CRNT_VLINE, par);
	crtc->off_pitch = aty_ld_le32(CRTC_OFF_PITCH, par);
	crtc->gen_cntl = aty_ld_le32(CRTC_GEN_CNTL, par);

#ifdef CONFIG_FB_ATY_GENERIC_LCD
	if (par->lcd_table != 0) {
		/* switch to shadow registers */
		aty_st_lcd(LCD_GEN_CNTL, (crtc->lcd_gen_cntl & ~CRTC_RW_SELECT) |
			   SHADOW_EN | SHADOW_RW_EN, par);

		crtc->shadow_h_tot_disp = aty_ld_le32(CRTC_H_TOTAL_DISP, par);
		crtc->shadow_h_sync_strt_wid = aty_ld_le32(CRTC_H_SYNC_STRT_WID, par);
		crtc->shadow_v_tot_disp = aty_ld_le32(CRTC_V_TOTAL_DISP, par);
		crtc->shadow_v_sync_strt_wid = aty_ld_le32(CRTC_V_SYNC_STRT_WID, par);

		aty_st_le32(LCD_GEN_CNTL, crtc->lcd_gen_cntl, par);
	}
#endif /* CONFIG_FB_ATY_GENERIC_LCD */
}