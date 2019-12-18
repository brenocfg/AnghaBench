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
typedef  int u64 ;
typedef  int u32 ;
struct niu_link_config {scalar_t__ loopback_mode; } ;
struct niu {int port; int /*<<< orphan*/  dev; struct niu_link_config link_config; } ;

/* Variables and functions */
 int BLTIME_300_CYCLES ; 
 int EINVAL ; 
 unsigned long ENET_SERDES_0_CTRL_CFG ; 
 unsigned long ENET_SERDES_0_PLL_CFG ; 
 unsigned long ENET_SERDES_0_TEST_CFG ; 
 unsigned long ENET_SERDES_1_CTRL_CFG ; 
 unsigned long ENET_SERDES_1_PLL_CFG ; 
 unsigned long ENET_SERDES_1_TEST_CFG ; 
 int ENET_SERDES_CTRL_EMPH_0_SHIFT ; 
 int ENET_SERDES_CTRL_EMPH_1_SHIFT ; 
 int ENET_SERDES_CTRL_EMPH_2_SHIFT ; 
 int ENET_SERDES_CTRL_EMPH_3_SHIFT ; 
 int ENET_SERDES_CTRL_LADJ_0_SHIFT ; 
 int ENET_SERDES_CTRL_LADJ_1_SHIFT ; 
 int ENET_SERDES_CTRL_LADJ_2_SHIFT ; 
 int ENET_SERDES_CTRL_LADJ_3_SHIFT ; 
 int ENET_SERDES_CTRL_SDET_0 ; 
 int ENET_SERDES_CTRL_SDET_1 ; 
 int ENET_SERDES_CTRL_SDET_2 ; 
 int ENET_SERDES_CTRL_SDET_3 ; 
 int ENET_SERDES_PLL_FBDIV0 ; 
 int ENET_SERDES_PLL_HRATE0 ; 
 int ENET_SERDES_PLL_HRATE1 ; 
 int ENET_SERDES_PLL_HRATE2 ; 
 int ENET_SERDES_PLL_HRATE3 ; 
 unsigned long ENET_SERDES_RESET ; 
 int ENET_SERDES_RESET_0 ; 
 int ENET_SERDES_RESET_1 ; 
 int ENET_SERDES_TEST_MD_0_SHIFT ; 
 int ENET_SERDES_TEST_MD_1_SHIFT ; 
 int ENET_SERDES_TEST_MD_2_SHIFT ; 
 int ENET_SERDES_TEST_MD_3_SHIFT ; 
 int ENET_TEST_MD_PAD_LOOPBACK ; 
 int ENODEV ; 
 int ESR_GLUE_CTRL0_BLTIME ; 
 int ESR_GLUE_CTRL0_BLTIME_SHIFT ; 
 int ESR_GLUE_CTRL0_RXLOSENAB ; 
 int ESR_GLUE_CTRL0_SRATE ; 
 int ESR_GLUE_CTRL0_SRATE_SHIFT ; 
 int ESR_GLUE_CTRL0_THCNT ; 
 int ESR_GLUE_CTRL0_THCNT_SHIFT ; 
 int ESR_INT_DET0_P0 ; 
 int ESR_INT_DET0_P1 ; 
 unsigned long ESR_INT_SIGNALS ; 
 int ESR_INT_SRDY0_P0 ; 
 int ESR_INT_SRDY0_P1 ; 
 int ESR_RXTX_CTRL_ENSTRETCH ; 
 int ESR_RXTX_CTRL_VMUXLO ; 
 int ESR_RXTX_CTRL_VMUXLO_SHIFT ; 
 scalar_t__ LOOPBACK_PHY ; 
 int esr_read_glue0 (struct niu*,unsigned long,int*) ; 
 int esr_read_rxtx_ctrl (struct niu*,unsigned long,int*) ; 
 int esr_write_glue0 (struct niu*,unsigned long,int) ; 
 int esr_write_rxtx_ctrl (struct niu*,unsigned long,int) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*,int,int,int) ; 
 int nr64 (unsigned long) ; 
 int /*<<< orphan*/  nw64 (unsigned long,int) ; 

__attribute__((used)) static int serdes_init_1g_serdes(struct niu *np)
{
	struct niu_link_config *lp = &np->link_config;
	unsigned long ctrl_reg, test_cfg_reg, pll_cfg, i;
	u64 ctrl_val, test_cfg_val, sig, mask, val;
	int err;
	u64 reset_val, val_rd;

	val = ENET_SERDES_PLL_HRATE0 | ENET_SERDES_PLL_HRATE1 |
		ENET_SERDES_PLL_HRATE2 | ENET_SERDES_PLL_HRATE3 |
		ENET_SERDES_PLL_FBDIV0;
	switch (np->port) {
	case 0:
		reset_val =  ENET_SERDES_RESET_0;
		ctrl_reg = ENET_SERDES_0_CTRL_CFG;
		test_cfg_reg = ENET_SERDES_0_TEST_CFG;
		pll_cfg = ENET_SERDES_0_PLL_CFG;
		break;
	case 1:
		reset_val =  ENET_SERDES_RESET_1;
		ctrl_reg = ENET_SERDES_1_CTRL_CFG;
		test_cfg_reg = ENET_SERDES_1_TEST_CFG;
		pll_cfg = ENET_SERDES_1_PLL_CFG;
		break;

	default:
		return -EINVAL;
	}
	ctrl_val = (ENET_SERDES_CTRL_SDET_0 |
		    ENET_SERDES_CTRL_SDET_1 |
		    ENET_SERDES_CTRL_SDET_2 |
		    ENET_SERDES_CTRL_SDET_3 |
		    (0x5 << ENET_SERDES_CTRL_EMPH_0_SHIFT) |
		    (0x5 << ENET_SERDES_CTRL_EMPH_1_SHIFT) |
		    (0x5 << ENET_SERDES_CTRL_EMPH_2_SHIFT) |
		    (0x5 << ENET_SERDES_CTRL_EMPH_3_SHIFT) |
		    (0x1 << ENET_SERDES_CTRL_LADJ_0_SHIFT) |
		    (0x1 << ENET_SERDES_CTRL_LADJ_1_SHIFT) |
		    (0x1 << ENET_SERDES_CTRL_LADJ_2_SHIFT) |
		    (0x1 << ENET_SERDES_CTRL_LADJ_3_SHIFT));
	test_cfg_val = 0;

	if (lp->loopback_mode == LOOPBACK_PHY) {
		test_cfg_val |= ((ENET_TEST_MD_PAD_LOOPBACK <<
				  ENET_SERDES_TEST_MD_0_SHIFT) |
				 (ENET_TEST_MD_PAD_LOOPBACK <<
				  ENET_SERDES_TEST_MD_1_SHIFT) |
				 (ENET_TEST_MD_PAD_LOOPBACK <<
				  ENET_SERDES_TEST_MD_2_SHIFT) |
				 (ENET_TEST_MD_PAD_LOOPBACK <<
				  ENET_SERDES_TEST_MD_3_SHIFT));
	}

	nw64(ENET_SERDES_RESET, reset_val);
	mdelay(20);
	val_rd = nr64(ENET_SERDES_RESET);
	val_rd &= ~reset_val;
	nw64(pll_cfg, val);
	nw64(ctrl_reg, ctrl_val);
	nw64(test_cfg_reg, test_cfg_val);
	nw64(ENET_SERDES_RESET, val_rd);
	mdelay(2000);

	/* Initialize all 4 lanes of the SERDES.  */
	for (i = 0; i < 4; i++) {
		u32 rxtx_ctrl, glue0;

		err = esr_read_rxtx_ctrl(np, i, &rxtx_ctrl);
		if (err)
			return err;
		err = esr_read_glue0(np, i, &glue0);
		if (err)
			return err;

		rxtx_ctrl &= ~(ESR_RXTX_CTRL_VMUXLO);
		rxtx_ctrl |= (ESR_RXTX_CTRL_ENSTRETCH |
			      (2 << ESR_RXTX_CTRL_VMUXLO_SHIFT));

		glue0 &= ~(ESR_GLUE_CTRL0_SRATE |
			   ESR_GLUE_CTRL0_THCNT |
			   ESR_GLUE_CTRL0_BLTIME);
		glue0 |= (ESR_GLUE_CTRL0_RXLOSENAB |
			  (0xf << ESR_GLUE_CTRL0_SRATE_SHIFT) |
			  (0xff << ESR_GLUE_CTRL0_THCNT_SHIFT) |
			  (BLTIME_300_CYCLES <<
			   ESR_GLUE_CTRL0_BLTIME_SHIFT));

		err = esr_write_rxtx_ctrl(np, i, rxtx_ctrl);
		if (err)
			return err;
		err = esr_write_glue0(np, i, glue0);
		if (err)
			return err;
	}


	sig = nr64(ESR_INT_SIGNALS);
	switch (np->port) {
	case 0:
		val = (ESR_INT_SRDY0_P0 | ESR_INT_DET0_P0);
		mask = val;
		break;

	case 1:
		val = (ESR_INT_SRDY0_P1 | ESR_INT_DET0_P1);
		mask = val;
		break;

	default:
		return -EINVAL;
	}

	if ((sig & mask) != val) {
		netdev_err(np->dev, "Port %u signal bits [%08x] are not [%08x]\n",
			   np->port, (int)(sig & mask), (int)val);
		return -ENODEV;
	}

	return 0;
}