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
struct st7789v {int /*<<< orphan*/  reset; int /*<<< orphan*/  power; } ;
struct drm_panel {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MIPI_DCS_ENTER_INVERT_MODE ; 
 int /*<<< orphan*/  MIPI_DCS_EXIT_SLEEP_MODE ; 
 int MIPI_DCS_PIXEL_FMT_18BIT ; 
 int /*<<< orphan*/  MIPI_DCS_SET_ADDRESS_MODE ; 
 int /*<<< orphan*/  MIPI_DCS_SET_PIXEL_FORMAT ; 
 int /*<<< orphan*/  ST7789V_FRCTRL2_CMD ; 
 int /*<<< orphan*/  ST7789V_GCTRL_CMD ; 
 int ST7789V_GCTRL_VGHS (int) ; 
 int ST7789V_GCTRL_VGLS (int) ; 
 int /*<<< orphan*/  ST7789V_LCMCTRL_CMD ; 
 int ST7789V_LCMCTRL_XBGR ; 
 int ST7789V_LCMCTRL_XMH ; 
 int ST7789V_LCMCTRL_XMX ; 
 int /*<<< orphan*/  ST7789V_NVGAMCTRL_CMD ; 
 int ST7789V_NVGAMCTRL_JN1 (int) ; 
 int ST7789V_NVGAMCTRL_VN1 (int) ; 
 int ST7789V_NVGAMCTRL_VN13 (int) ; 
 int ST7789V_NVGAMCTRL_VN2 (int) ; 
 int ST7789V_NVGAMCTRL_VN20 (int) ; 
 int ST7789V_NVGAMCTRL_VN27 (int) ; 
 int ST7789V_NVGAMCTRL_VN36 (int) ; 
 int ST7789V_NVGAMCTRL_VN4 (int) ; 
 int ST7789V_NVGAMCTRL_VN43 (int) ; 
 int ST7789V_NVGAMCTRL_VN50 (int) ; 
 int ST7789V_NVGAMCTRL_VN57 (int) ; 
 int ST7789V_NVGAMCTRL_VN59 (int) ; 
 int ST7789V_NVGAMCTRL_VN6 (int) ; 
 int ST7789V_NVGAMCTRL_VN61 (int) ; 
 int ST7789V_NVGAMCTRL_VN62 (int) ; 
 int ST7789V_NVGAMCTRL_VN63 (int) ; 
 int /*<<< orphan*/  ST7789V_PORCTRL_CMD ; 
 int ST7789V_PORCTRL_IDLE_BP (int) ; 
 int ST7789V_PORCTRL_IDLE_FP (int) ; 
 int ST7789V_PORCTRL_PARTIAL_BP (int) ; 
 int ST7789V_PORCTRL_PARTIAL_FP (int) ; 
 int /*<<< orphan*/  ST7789V_PVGAMCTRL_CMD ; 
 int ST7789V_PVGAMCTRL_JP1 (int) ; 
 int ST7789V_PVGAMCTRL_VP1 (int) ; 
 int ST7789V_PVGAMCTRL_VP13 (int) ; 
 int ST7789V_PVGAMCTRL_VP2 (int) ; 
 int ST7789V_PVGAMCTRL_VP20 (int) ; 
 int ST7789V_PVGAMCTRL_VP27 (int) ; 
 int ST7789V_PVGAMCTRL_VP36 (int) ; 
 int ST7789V_PVGAMCTRL_VP4 (int) ; 
 int ST7789V_PVGAMCTRL_VP43 (int) ; 
 int ST7789V_PVGAMCTRL_VP50 (int) ; 
 int ST7789V_PVGAMCTRL_VP57 (int) ; 
 int ST7789V_PVGAMCTRL_VP59 (int) ; 
 int ST7789V_PVGAMCTRL_VP6 (int) ; 
 int ST7789V_PVGAMCTRL_VP61 (int) ; 
 int ST7789V_PVGAMCTRL_VP62 (int) ; 
 int ST7789V_PVGAMCTRL_VP63 (int) ; 
 int ST7789V_PWCTRL1_AVCL (int) ; 
 int ST7789V_PWCTRL1_AVDD (int) ; 
 int /*<<< orphan*/  ST7789V_PWCTRL1_CMD ; 
 int ST7789V_PWCTRL1_MAGIC ; 
 int ST7789V_PWCTRL1_VDS (int) ; 
 int /*<<< orphan*/  ST7789V_RAMCTRL_CMD ; 
 int ST7789V_RAMCTRL_DM_RGB ; 
 int ST7789V_RAMCTRL_EPF (int) ; 
 int ST7789V_RAMCTRL_MAGIC ; 
 int ST7789V_RAMCTRL_RM_RGB ; 
 int /*<<< orphan*/  ST7789V_RGBCTRL_CMD ; 
 int ST7789V_RGBCTRL_HBP (int) ; 
 int ST7789V_RGBCTRL_HSYNC_HIGH ; 
 int ST7789V_RGBCTRL_PCLK_HIGH ; 
 int ST7789V_RGBCTRL_RCM (int) ; 
 int ST7789V_RGBCTRL_VBP (int) ; 
 int ST7789V_RGBCTRL_VSYNC_HIGH ; 
 int ST7789V_RGBCTRL_WO ; 
 int /*<<< orphan*/  ST7789V_TEST (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ST7789V_VCOMS_CMD ; 
 int /*<<< orphan*/  ST7789V_VDVS_CMD ; 
 int /*<<< orphan*/  ST7789V_VDVVRHEN_CMD ; 
 int ST7789V_VDVVRHEN_CMDEN ; 
 int /*<<< orphan*/  ST7789V_VRHS_CMD ; 
 int /*<<< orphan*/  gpiod_set_value (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 struct st7789v* panel_to_st7789v (struct drm_panel*) ; 
 int regulator_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  st7789v_write_command (struct st7789v*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  st7789v_write_data (struct st7789v*,int) ; 

__attribute__((used)) static int st7789v_prepare(struct drm_panel *panel)
{
	struct st7789v *ctx = panel_to_st7789v(panel);
	int ret;

	ret = regulator_enable(ctx->power);
	if (ret)
		return ret;

	gpiod_set_value(ctx->reset, 1);
	msleep(30);
	gpiod_set_value(ctx->reset, 0);
	msleep(120);

	ST7789V_TEST(ret, st7789v_write_command(ctx, MIPI_DCS_EXIT_SLEEP_MODE));

	/* We need to wait 120ms after a sleep out command */
	msleep(120);

	ST7789V_TEST(ret, st7789v_write_command(ctx,
						MIPI_DCS_SET_ADDRESS_MODE));
	ST7789V_TEST(ret, st7789v_write_data(ctx, 0));

	ST7789V_TEST(ret, st7789v_write_command(ctx,
						MIPI_DCS_SET_PIXEL_FORMAT));
	ST7789V_TEST(ret, st7789v_write_data(ctx,
					     (MIPI_DCS_PIXEL_FMT_18BIT << 4) |
					     (MIPI_DCS_PIXEL_FMT_18BIT)));

	ST7789V_TEST(ret, st7789v_write_command(ctx, ST7789V_PORCTRL_CMD));
	ST7789V_TEST(ret, st7789v_write_data(ctx, 0xc));
	ST7789V_TEST(ret, st7789v_write_data(ctx, 0xc));
	ST7789V_TEST(ret, st7789v_write_data(ctx, 0));
	ST7789V_TEST(ret, st7789v_write_data(ctx, ST7789V_PORCTRL_IDLE_BP(3) |
					     ST7789V_PORCTRL_IDLE_FP(3)));
	ST7789V_TEST(ret, st7789v_write_data(ctx,
					     ST7789V_PORCTRL_PARTIAL_BP(3) |
					     ST7789V_PORCTRL_PARTIAL_FP(3)));

	ST7789V_TEST(ret, st7789v_write_command(ctx, ST7789V_GCTRL_CMD));
	ST7789V_TEST(ret, st7789v_write_data(ctx, ST7789V_GCTRL_VGLS(5) |
					     ST7789V_GCTRL_VGHS(3)));

	ST7789V_TEST(ret, st7789v_write_command(ctx, ST7789V_VCOMS_CMD));
	ST7789V_TEST(ret, st7789v_write_data(ctx, 0x2b));

	ST7789V_TEST(ret, st7789v_write_command(ctx, ST7789V_LCMCTRL_CMD));
	ST7789V_TEST(ret, st7789v_write_data(ctx, ST7789V_LCMCTRL_XMH |
					     ST7789V_LCMCTRL_XMX |
					     ST7789V_LCMCTRL_XBGR));

	ST7789V_TEST(ret, st7789v_write_command(ctx, ST7789V_VDVVRHEN_CMD));
	ST7789V_TEST(ret, st7789v_write_data(ctx, ST7789V_VDVVRHEN_CMDEN));

	ST7789V_TEST(ret, st7789v_write_command(ctx, ST7789V_VRHS_CMD));
	ST7789V_TEST(ret, st7789v_write_data(ctx, 0xf));

	ST7789V_TEST(ret, st7789v_write_command(ctx, ST7789V_VDVS_CMD));
	ST7789V_TEST(ret, st7789v_write_data(ctx, 0x20));

	ST7789V_TEST(ret, st7789v_write_command(ctx, ST7789V_FRCTRL2_CMD));
	ST7789V_TEST(ret, st7789v_write_data(ctx, 0xf));

	ST7789V_TEST(ret, st7789v_write_command(ctx, ST7789V_PWCTRL1_CMD));
	ST7789V_TEST(ret, st7789v_write_data(ctx, ST7789V_PWCTRL1_MAGIC));
	ST7789V_TEST(ret, st7789v_write_data(ctx, ST7789V_PWCTRL1_AVDD(2) |
					     ST7789V_PWCTRL1_AVCL(2) |
					     ST7789V_PWCTRL1_VDS(1)));

	ST7789V_TEST(ret, st7789v_write_command(ctx, ST7789V_PVGAMCTRL_CMD));
	ST7789V_TEST(ret, st7789v_write_data(ctx, ST7789V_PVGAMCTRL_VP63(0xd)));
	ST7789V_TEST(ret, st7789v_write_data(ctx, ST7789V_PVGAMCTRL_VP1(0xca)));
	ST7789V_TEST(ret, st7789v_write_data(ctx, ST7789V_PVGAMCTRL_VP2(0xe)));
	ST7789V_TEST(ret, st7789v_write_data(ctx, ST7789V_PVGAMCTRL_VP4(8)));
	ST7789V_TEST(ret, st7789v_write_data(ctx, ST7789V_PVGAMCTRL_VP6(9)));
	ST7789V_TEST(ret, st7789v_write_data(ctx, ST7789V_PVGAMCTRL_VP13(7)));
	ST7789V_TEST(ret, st7789v_write_data(ctx, ST7789V_PVGAMCTRL_VP20(0x2d)));
	ST7789V_TEST(ret, st7789v_write_data(ctx, ST7789V_PVGAMCTRL_VP27(0xb) |
					     ST7789V_PVGAMCTRL_VP36(3)));
	ST7789V_TEST(ret, st7789v_write_data(ctx, ST7789V_PVGAMCTRL_VP43(0x3d)));
	ST7789V_TEST(ret, st7789v_write_data(ctx, ST7789V_PVGAMCTRL_JP1(3) |
					     ST7789V_PVGAMCTRL_VP50(4)));
	ST7789V_TEST(ret, st7789v_write_data(ctx, ST7789V_PVGAMCTRL_VP57(0xa)));
	ST7789V_TEST(ret, st7789v_write_data(ctx, ST7789V_PVGAMCTRL_VP59(0xa)));
	ST7789V_TEST(ret, st7789v_write_data(ctx, ST7789V_PVGAMCTRL_VP61(0x1b)));
	ST7789V_TEST(ret, st7789v_write_data(ctx, ST7789V_PVGAMCTRL_VP62(0x28)));

	ST7789V_TEST(ret, st7789v_write_command(ctx, ST7789V_NVGAMCTRL_CMD));
	ST7789V_TEST(ret, st7789v_write_data(ctx, ST7789V_NVGAMCTRL_VN63(0xd)));
	ST7789V_TEST(ret, st7789v_write_data(ctx, ST7789V_NVGAMCTRL_VN1(0xca)));
	ST7789V_TEST(ret, st7789v_write_data(ctx, ST7789V_NVGAMCTRL_VN2(0xf)));
	ST7789V_TEST(ret, st7789v_write_data(ctx, ST7789V_NVGAMCTRL_VN4(8)));
	ST7789V_TEST(ret, st7789v_write_data(ctx, ST7789V_NVGAMCTRL_VN6(8)));
	ST7789V_TEST(ret, st7789v_write_data(ctx, ST7789V_NVGAMCTRL_VN13(7)));
	ST7789V_TEST(ret, st7789v_write_data(ctx, ST7789V_NVGAMCTRL_VN20(0x2e)));
	ST7789V_TEST(ret, st7789v_write_data(ctx, ST7789V_NVGAMCTRL_VN27(0xc) |
					     ST7789V_NVGAMCTRL_VN36(5)));
	ST7789V_TEST(ret, st7789v_write_data(ctx, ST7789V_NVGAMCTRL_VN43(0x40)));
	ST7789V_TEST(ret, st7789v_write_data(ctx, ST7789V_NVGAMCTRL_JN1(3) |
					     ST7789V_NVGAMCTRL_VN50(4)));
	ST7789V_TEST(ret, st7789v_write_data(ctx, ST7789V_NVGAMCTRL_VN57(9)));
	ST7789V_TEST(ret, st7789v_write_data(ctx, ST7789V_NVGAMCTRL_VN59(0xb)));
	ST7789V_TEST(ret, st7789v_write_data(ctx, ST7789V_NVGAMCTRL_VN61(0x1b)));
	ST7789V_TEST(ret, st7789v_write_data(ctx, ST7789V_NVGAMCTRL_VN62(0x28)));

	ST7789V_TEST(ret, st7789v_write_command(ctx, MIPI_DCS_ENTER_INVERT_MODE));

	ST7789V_TEST(ret, st7789v_write_command(ctx, ST7789V_RAMCTRL_CMD));
	ST7789V_TEST(ret, st7789v_write_data(ctx, ST7789V_RAMCTRL_DM_RGB |
					     ST7789V_RAMCTRL_RM_RGB));
	ST7789V_TEST(ret, st7789v_write_data(ctx, ST7789V_RAMCTRL_EPF(3) |
					     ST7789V_RAMCTRL_MAGIC));

	ST7789V_TEST(ret, st7789v_write_command(ctx, ST7789V_RGBCTRL_CMD));
	ST7789V_TEST(ret, st7789v_write_data(ctx, ST7789V_RGBCTRL_WO |
					     ST7789V_RGBCTRL_RCM(2) |
					     ST7789V_RGBCTRL_VSYNC_HIGH |
					     ST7789V_RGBCTRL_HSYNC_HIGH |
					     ST7789V_RGBCTRL_PCLK_HIGH));
	ST7789V_TEST(ret, st7789v_write_data(ctx, ST7789V_RGBCTRL_VBP(8)));
	ST7789V_TEST(ret, st7789v_write_data(ctx, ST7789V_RGBCTRL_HBP(20)));

	return 0;
}