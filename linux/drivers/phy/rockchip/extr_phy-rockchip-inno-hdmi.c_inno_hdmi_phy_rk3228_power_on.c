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
struct post_pll_config {int postdiv; int tmdsclock; int /*<<< orphan*/  fbdiv; int /*<<< orphan*/  prediv; } ;
struct phy_config {int /*<<< orphan*/ * regs; } ;
struct inno_hdmi_phy {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int RK3228_BANDGAP_ENABLE ; 
 int RK3228_PDATAEN_DISABLE ; 
 int /*<<< orphan*/  RK3228_POST_PLL_FB_DIV_7_0 (int /*<<< orphan*/ ) ; 
 int RK3228_POST_PLL_FB_DIV_8 (int /*<<< orphan*/ ) ; 
 int RK3228_POST_PLL_FB_DIV_8_MASK ; 
 int RK3228_POST_PLL_LOCK_STATUS ; 
 int RK3228_POST_PLL_POST_DIV (int) ; 
 int RK3228_POST_PLL_POST_DIV_ENABLE ; 
 int RK3228_POST_PLL_POST_DIV_MASK ; 
 int RK3228_POST_PLL_POWER_DOWN ; 
 int RK3228_POST_PLL_PRE_DIV (int /*<<< orphan*/ ) ; 
 int RK3228_POST_PLL_PRE_DIV_MASK ; 
 int RK3228_PRE_PLL_POWER_DOWN ; 
 int RK3228_TMDS_DRIVER_ENABLE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int inno_poll (struct inno_hdmi_phy*,int,int,int,int,int) ; 
 int /*<<< orphan*/  inno_update_bits (struct inno_hdmi_phy*,int,int,int) ; 
 int /*<<< orphan*/  inno_write (struct inno_hdmi_phy*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static int
inno_hdmi_phy_rk3228_power_on(struct inno_hdmi_phy *inno,
			      const struct post_pll_config *cfg,
			      const struct phy_config *phy_cfg)
{
	int ret;
	u32 v;

	inno_update_bits(inno, 0x02, RK3228_PDATAEN_DISABLE,
			 RK3228_PDATAEN_DISABLE);
	inno_update_bits(inno, 0xe0, RK3228_PRE_PLL_POWER_DOWN |
			 RK3228_POST_PLL_POWER_DOWN,
			 RK3228_PRE_PLL_POWER_DOWN |
			 RK3228_POST_PLL_POWER_DOWN);

	/* Post-PLL update */
	inno_update_bits(inno, 0xe9, RK3228_POST_PLL_PRE_DIV_MASK,
			 RK3228_POST_PLL_PRE_DIV(cfg->prediv));
	inno_update_bits(inno, 0xeb, RK3228_POST_PLL_FB_DIV_8_MASK,
			 RK3228_POST_PLL_FB_DIV_8(cfg->fbdiv));
	inno_write(inno, 0xea, RK3228_POST_PLL_FB_DIV_7_0(cfg->fbdiv));

	if (cfg->postdiv == 1) {
		inno_update_bits(inno, 0xe9, RK3228_POST_PLL_POST_DIV_ENABLE,
				 0);
	} else {
		int div = cfg->postdiv / 2 - 1;

		inno_update_bits(inno, 0xe9, RK3228_POST_PLL_POST_DIV_ENABLE,
				 RK3228_POST_PLL_POST_DIV_ENABLE);
		inno_update_bits(inno, 0xeb, RK3228_POST_PLL_POST_DIV_MASK,
				 RK3228_POST_PLL_POST_DIV(div));
	}

	for (v = 0; v < 4; v++)
		inno_write(inno, 0xef + v, phy_cfg->regs[v]);

	inno_update_bits(inno, 0xe0, RK3228_PRE_PLL_POWER_DOWN |
			 RK3228_POST_PLL_POWER_DOWN, 0);
	inno_update_bits(inno, 0xe1, RK3228_BANDGAP_ENABLE,
			 RK3228_BANDGAP_ENABLE);
	inno_update_bits(inno, 0xe1, RK3228_TMDS_DRIVER_ENABLE,
			 RK3228_TMDS_DRIVER_ENABLE);

	/* Wait for post PLL lock */
	ret = inno_poll(inno, 0xeb, v, v & RK3228_POST_PLL_LOCK_STATUS,
			100, 100000);
	if (ret) {
		dev_err(inno->dev, "Post-PLL locking failed\n");
		return ret;
	}

	if (cfg->tmdsclock > 340000000)
		msleep(100);

	inno_update_bits(inno, 0x02, RK3228_PDATAEN_DISABLE, 0);
	return 0;
}